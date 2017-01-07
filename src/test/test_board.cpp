#include <iostream>
#include <string>
#include <apbattle/battleship_agent.h>

#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cout << "args: <windowTitle>\n";
		return 0;
	}

	bship::PlayerBattleBoard Board(argv[1]);

	for(;;){
		Board.updateWindow();
	}

	return 0;
}