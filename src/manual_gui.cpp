#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cereal/archives/json.hpp>

// Custom
#include <apbattle/socket_client.h>
#include <apbattle/battleship_gui.h>
#include <apbattle/battle_board.h>
#include <apbattle/bship_common.h>


int main(int argc, char *argv[])
{


	bship::BattleshipGui bGui;
	bool success, isNewClick = false;
	int row, col = 0;

	bship::BattleBoard BBoard;

	std::vector<bship::Ship> ships = BBoard.getShipLocations();

	{
		std::stringstream ss;
		cereal::JSONOutputArchive archive( ss );
		archive(CEREAL_NVP(ships[0].name),
				    CEREAL_NVP(ships[0].row), 
				    CEREAL_NVP(ships[0].col),
				    CEREAL_NVP(ships[0].direction));
		std::cout << ss << "\n";
	}




	for (;;) {

		success = bGui.updateWindow();
		if (!success) {return 0;}

		success = bGui.handleEvents(isNewClick, col, row); // have to invert from gui
		if (!success) {return 0;}

		if (isNewClick) {

			// user input obtained here
			bship::HitStatus hitStatus;
			bool didSinkShip = false;
			bship::ShipName sunkenShipName;

			BBoard.checkGridLocation(row, col, hitStatus, didSinkShip, sunkenShipName);
			if (didSinkShip)
			{
				std::cout << "You have sunk my " << bship::shipNameLookup.at(sunkenShipName) << "\n";
			}
			success = bGui.setHit(col, row, hitStatus); // todo
			if (!success) {return 0;}
		}

	}
	return 1;
}