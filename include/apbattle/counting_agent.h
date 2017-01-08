#ifndef __counting__agent__
#define __counting__agent__

#include <apbattle/battleship_agent.h>

namespace bship {

class CountingAgent: public BattleshipAgent
{
public:
	CountingAgent(std::string host, unsigned short port,
	            std::string playerName, bool isHost, 
	            bool enableLogging = false, int inflationFactor = 1);

	~CountingAgent() {};

private:
	void resetBoard();

	int guessLocation();

}; // class

} // ns

#endif