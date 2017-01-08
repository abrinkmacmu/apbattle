
#include <unistd.h>
#include <apbattle/manual_agent.h>

bship::ManualAgent::ManualAgent(std::string host, unsigned short port,
                                std::string playerName, bool isHost):
	BattleshipAgent(host, port, playerName, isHost)
{

}

void bship::ManualAgent::resetBoard()
{
	BattleshipAgent::resetBoard();
}

int bship::ManualAgent::guessLocation()
{
	int row = -1;
	int col = -1;
	bool isNewClick = false;

	while(!isNewClick){
		enemyBoard.handleGUIEvents(isNewClick, row, col);
		usleep(1e4); // sleep for 10,000 usec = .01 sec
	}
	return (10*row + col);
}