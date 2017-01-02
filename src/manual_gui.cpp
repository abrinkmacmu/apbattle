#include <iostream>
#include <string>
#include <vector>

// Custom
#include <apbattle/socket_client.h>
#include <apbattle/battleship_gui.h>
#include <apbattle/battle_board.h>

int main(int argc, char *argv[])
{

	bship::BattleshipGui bGui;
	bool success, isNewClick = false;
	int row, col = 0;



	for(;;){

		success = bGui.updateWindow();
		if(!success){return 0;}
		
		success = bGui.handleEvents(isNewClick, row, col);
		if(!success){return 0;}
		
		if(isNewClick){

			// user input obtained here
			success = bGui.setHit(row, col, bship::Hit); // todo
			if(!success){return 0;}	
		}

	}
	return 1;
}