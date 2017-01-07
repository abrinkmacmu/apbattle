
#include <iostream>
#include <unistd.h> //sleep
#include <cstdlib> // rand
#include <ctime>
#include <fstream>

#include <apbattle/bship_common.h>
#include <apbattle/battleship_agent.h>



bship::BattleshipAgent::BattleshipAgent(
  std::string host, unsigned short port,
  std::string playerName, bool isHost):
	socketConnection_(host, port, isHost),
	host_(host),
	port_(port),
	log_file_path_("/home/apark/cpp_projects/battship/apbattle/data/"),
	enemyBoard("enemy", std::string(playerName + ": Enemy-View")),
	playerBoard("player", std::string(playerName + ": Player-View"))
{
	
	std::time_t now = std::time(0);
	log_file_name_ = std::string(ctime(&now));
}



void bship::BattleshipAgent::playGame(bool goFirst)
{
	for (;;) {
		resetBoard();
		bool gameIsOver = false;
		if (goFirst) {
			std::cout << "In attack phase\n";
			attackPhase(gameIsOver);
		}

		while (!gameIsOver)
		{
			std::cout << "In defend phase\n";
			defendPhase(gameIsOver);
			if (gameIsOver) { goFirst = true; break;}
			usleep(1e6);
			std::cout << "In attack phase\n";
			attackPhase(gameIsOver);
			if (gameIsOver) { goFirst = false; break;}
			usleep(1e6);
		}
		handleGameOver();
	}
}

void bship::BattleshipAgent::resetBoard()
{
	total_moves_ = 0;
	enemyBoard.reset();
	playerBoard.reset();


	std::srand(std::time(0)); // initialize rand seed
	std::time_t now = std::time(0);
	log_file_name_ = std::string(ctime(&now));
}



void bship::BattleshipAgent::attackPhase(bool& gameIsOver) {

	int guessRowCol = guessLocation();
	std::cout << "Attack guess: " << guessRowCol << "\n";
	std::string gMsg = createGuessMsg(guessRowCol);
	socketConnection_.write(gMsg);
	std::string msg;
	if (socketConnection_.read(msg)) {
		HitStatus hs;
		ShipName sn;
		bool gameover = false;
		parseResponseMsg(msg, hs, sn, gameover);
		if (gameover) {
			gameIsOver = true;
			return;
		}
		enemyBoard.setHit(guessRowCol / 10, guessRowCol % 10, hs);
		enemyBoard.updateWindow();
	} else {
		std::cerr << "Error: Socket Read error in Attack phase\n";
	}
}




void bship::BattleshipAgent::defendPhase(bool& gameIsOver) {

	std::string msg;
	if (socketConnection_.read(msg)) {
		int guess;
		parseGuessMsg(msg, guess);
		HitStatus status;
		bool didSinkShip;
		ShipName shipName;
		std::cout << "Defend guess: " << guess << ", " << guess / 10 << ", " << guess % 10 << "\n";
		playerBoard.checkGridLocation(guess / 10, guess % 10, status, didSinkShip, shipName);
		std::string resMsg = createResponseMsg(status, shipName , false); // todo gameover condition
		socketConnection_.write(resMsg);
		playerBoard.updateWindow();

	} else {
		std::cerr << "Error: Socket Read error in defend phase\n";
	}

}

void bship::BattleshipAgent::handleGameOver() {

}




int bship::BattleshipAgent::guessLocation()
{
	// default 'dumb' implementation
	std::srand(std::time(0)); // initialize rand seed
	return std::rand() % 100;
}

void bship::BattleshipAgent::logAttackPhase(
  int my_guess, std::string enemy_response, std::string enemy_sunk)
{
	std::ofstream file;
	file.open(log_file_path_ + log_file_name_, std::ios::app);
	file << total_moves_ << ", "
	     << "attack " << ", "
	     << my_guess << ", "
	     << enemy_response << ", "
	     << enemy_sunk << "\n";

	file.close();
	return;
}

void bship::BattleshipAgent::logDefendPhase(
  int enemy_guess, std::string my_response, std::string my_sunk)
{
	std::ofstream file;
	file.open(log_file_path_ + log_file_name_, std::ios::app);
	file << total_moves_ << ", "
	     << "defend " << ", "
	     << enemy_guess << " , "
	     << my_response << ", "
	     << my_sunk << "\n";

	file.close();
	return;
}





