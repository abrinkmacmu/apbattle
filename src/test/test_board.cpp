#include <iostream>
#include <string>
#include <apbattle/battleship_agent.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		std::cout << "args: <owner> <window_title>\n";
		return 0;
	}

	bship::BattleBoard Board(argv[1], argv[2]) ;

	return 0;
}