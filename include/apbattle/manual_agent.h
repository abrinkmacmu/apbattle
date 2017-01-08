#ifndef __manual__agent__
#define __manual__agent__

#include <apbattle/battleship_agent.h>

namespace bship {

class ManualAgent: public BattleshipAgent
{
public:
	ManualAgent(std::string host, unsigned short port,
	            std::string playerName, bool isHost);

	~ManualAgent() {};

private:
	void resetBoard();

	int guessLocation();

}; // class

} // ns

#endif