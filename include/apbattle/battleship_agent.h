#ifndef __battleship__agent__
#define __battleship__agent__

namespace bship {

class BattleshipAgent{
public:

	/**
	 * @brief spins up reading thread and allocates fields
	 */
	BattleshipAgent(
		std::string host, std::string host_port
		std::string client, std::string client_port);

	virtual ~BattleshipAgent();

	void playGame();

private:

	void connectToSocket();

	virtual void guessLocation();

	void respondToRequest();

	void logMoves();

	void sendMessage();

	void receiveMessage();

}; // class BattleshipAgent

} // ns bship

#endif