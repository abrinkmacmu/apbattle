#ifndef __battleship__agent__
#define __battleship__agent__

#include <apbattle/socket_connection.h>
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

	virtual ~BattleshipAgent();

	void playGame();

private:

	virtual void guessLocation();

	void respondToRequest();

	void logMoves();

	

	std::string host_;
	unsigned short port_;

	
	SocketConnection socketConnection_;
	std::string log_file_name_;



}; // class BattleshipAgent

} // ns bship

#endif