#ifndef __battleship__agent__
#define __battleship__agent__

#include <apbattle/socket_connection.h>
#include <apbattle/player_battle_board.h>
#include <apbattle/enemy_battle_board.h>
#include <string>
#include <queue>
#include <future>


namespace bship {

class BattleshipAgent {
public:

	/**
	 * @brief spins up reading thread and allocates fields
	 */
	BattleshipAgent(
	  std::string host, unsigned short port,
	  std::string playerName, bool isHost,
	  bool enableLogging=false);

	virtual ~BattleshipAgent() {};

	void playGame(bool goFirst);

protected:

	virtual void resetBoard();

	virtual int guessLocation();

	void attackPhase(bool& gameIsOver);

	void defendPhase(bool& gameIsOver);

	void initiateConnection();

	void respondToConnection();

	void logAttackPhase(int my_guess, std::string enemy_response, std::string enemy_sunk);

	void logDefendPhase(int enemy_guess, std::string my_response, std::string my_sunk);

	// TODO logShipConfiguration();


	std::string host_;
	unsigned short port_;
	SocketConnection socketConnection_;
	std::string log_file_name_;
	std::string log_file_path_;
	int total_guesses_;
	EnemyBattleBoard enemyBoard;
	PlayerBattleBoard playerBoard;
	std::vector<bool> guess_list_;




}; // class BattleshipAgent

} // ns bship

#endif