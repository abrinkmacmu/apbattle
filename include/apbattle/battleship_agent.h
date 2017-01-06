#ifndef __battleship__agent__
#define __battleship__agent__

#include <apbattle/socket_client.h>
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
		std::string host, std::string host_port,
		std::string client, std::string client_port);

	virtual ~BattleshipAgent();

	void playGame();

private:

	void connectToSocket();

	virtual void guessLocation();

	void respondToRequest();

	void logMoves();

	void sendMessage();

	Client socketClient_;

	std::future<std::queue<std::string>> future_read_queue_;



}; // class BattleshipAgent

} // ns bship

#endif