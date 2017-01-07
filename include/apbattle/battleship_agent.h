#ifndef __battleship__agent__
#define __battleship__agent__

#include <apbattle/socket_connection.h>
#include <apbattle/battle_board.h>
#include <string>
#include <queue>
#include <future>


namespace bship {

class BattleshipAgent{
public:

	/**
	 * @brief spins up reading thread and allocates fields
	 */
	BattleshipAgent(
		std::string host, unsigned short port,
  std::string playerName, bool isHost);

	virtual ~BattleshipAgent(){};

	void playGame(bool goFirst);

private:

	void resetBoard();

	void attackPhase(bool& gameIsOver);

	void defendPhase(bool& gameIsOver);

	void handleGameOver();

	virtual int guessLocation();

	void logAttackPhase(int my_guess, std::string enemy_response, std::string enemy_sunk);

	void logDefendPhase(int enemy_guess, std::string my_response, std::string my_sunk);

	// TODO logShipConfiguration();

	
	std::string host_;
	unsigned short port_;	
	SocketConnection socketConnection_;
	std::string log_file_name_;
	std::string log_file_path_;
	int total_moves_;
	BattleBoard enemyBoard;
	BattleBoard playerBoard;




}; // class BattleshipAgent

} // ns bship

#endif