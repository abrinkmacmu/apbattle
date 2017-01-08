
#include <iostream>
#include <apbattle/counting_agent.h>

bship::CountingAgent::CountingAgent(std::string host, unsigned short port,
                                std::string playerName, bool isHost, 
                                bool enableLogging, int inflationFactor):
	BattleshipAgent(host, port, playerName, isHost)
{
	enemyBoard.setInflation(inflationFactor);
}

void bship::CountingAgent::resetBoard()
{
	BattleshipAgent::resetBoard();
}

int bship::CountingAgent::guessLocation()
{
	int row = -1;
	int col = -1;

	enemyBoard.computeProbabilityDistribution(row, col);

	if(row < 0 or row > 9 or col < 0 or col > 9){
		std::cout << "Error: Counting Agent Guess is bad! value: " << (10*row+col) <<"\n";
		return 0;
	}
	return (10*row + col);
}