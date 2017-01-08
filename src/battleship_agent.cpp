
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
	enemyBoard( std::string(playerName + ": Enemy-View")),
	playerBoard( std::string(playerName + ": Player-View")),
	guess_list_(100, false)
{
	std::time_t now = std::time(0);
	log_file_name_ = std::string(ctime(&now));
}



void bship::BattleshipAgent::playGame(bool goFirst)
{
	for (;;) {
		std::cout << "Initiating new game!\n\n";
		if(goFirst){
			initiateConnection();
		}else{
			respondToConnection();
		}

		resetBoard();
		bool gameIsOver = false;
		if (goFirst) {
			//std::cout << "In attack phase\n";
			attackPhase(gameIsOver);
		}

		while (!gameIsOver)
		{
			//std::cout << "In defend phase\n";
			defendPhase(gameIsOver);
			if (gameIsOver) { goFirst = true; break;}
			usleep(1e4); // 4e6 usec = .01 sec
			//std::cout << "In attack phase\n";
			attackPhase(gameIsOver);
			if (gameIsOver) { goFirst = false; break;}
			usleep(1e5); // 4e6 usec = .01 sec
		}
	}
}

void bship::BattleshipAgent::resetBoard()
{
	total_moves_ = 0;
	for (int i = 0; i < guess_list_.size(); i++) { guess_list_[i] = false;}
	enemyBoard.reset();
	playerBoard.reset();

	enemyBoard.updateWindow();
	playerBoard.updateWindow();

	std::time_t now = std::time(0);
	log_file_name_ = std::string(ctime(&now));
}

int bship::BattleshipAgent::guessLocation()
{
	// default 'dumb' implementation
	bool invalidGuess = true;
	int guess = 0;
	while (invalidGuess) {
		guess = std::rand() % 100;
		if (false == guess_list_[guess]) {
			guess_list_[guess] = true;
			invalidGuess = false;
		}
	}

	return guess;
}



void bship::BattleshipAgent::attackPhase(bool& gameIsOver) {

	int guessRowCol = guessLocation();
	std::string gMsg = createGuessMsg(guessRowCol);
	socketConnection_.write(gMsg);
	//std::cout << "SOCKET WRITE: Guess " << gMsg << "\n";

	std::string msg;
	if (socketConnection_.read(msg)) {

		HitStatus hs;
		ShipName sn;
		bool gameover = false;
		parseResponseMsg(msg, hs, sn, gameover);

		// print sunk ship for manual agents
		if(sn != bship::None){ std::cout << "From Enemy: You have sunk my : " << shipNameLookup.at(sn) << "\n";}
		//std::cout << "SOCKET READ: Response " << msg << "\n";

		if (gameover) {
			std::cout << "GAMEOVER! you have WON!!!!\n\n";
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
		//std::cout << "SOCKET READ: Guess " << msg << "\n";

		HitStatus status;
		ShipName sunkShipName;;
		playerBoard.checkGridLocation(guess / 10, guess % 10, status, sunkShipName);
		gameIsOver = playerBoard.checkGameoverCondition();
		std::string resMsg = createResponseMsg(status, sunkShipName , gameIsOver); // todo gameover condition
		socketConnection_.write(resMsg);
		if(status == bship::Hit){
			std::cout << "Oh No, you it me at " << guess << "\n";
		}
		//std::cout << "SOCKET WRITE: Response " << resMsg << "\n";

		if (gameIsOver) {
			std::cout << "GAMEOVER! you have LOST :c\n\n";
			return;
		}

		playerBoard.updateWindow();

	} else {
		std::cerr << "Error: Socket Read error in defend phase\n";
	}

}

void bship::BattleshipAgent::initiateConnection() {
	std::string cMsg = createConnectionMsg(true, true);
	socketConnection_.write(cMsg);
	std::string newMsg;
	socketConnection_.read(newMsg);

	bool reset_requested; bool ready_to_play;
	parseConnectionMsg(newMsg, reset_requested, ready_to_play);
	std::cout << "Connection successfully initiated\n";
	usleep(1e6);

}

void bship::BattleshipAgent::respondToConnection() {
	std::string newMsg;
	socketConnection_.read(newMsg);

	bool reset_requested; bool ready_to_play;
	parseConnectionMsg(newMsg, reset_requested, ready_to_play);

	std::string cMsg = createConnectionMsg(true, true);
	socketConnection_.write(cMsg);

	std::cout << "Connection successfully received\n";
	usleep(1e6);
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





