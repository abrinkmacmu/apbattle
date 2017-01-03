
#include <stdlib.h>
#include <apbattle/battle_board.h>
#include <apbattle/bship_common.h>
#include <time.h>

bship::BattleBoard::BattleBoard():
	enemy_map_(10, std::vector<int>(10, Unknown)),
	player_map_(10, std::vector<int>(10, Unknown))
{

	generateRandomShips();

	consolePrintBoard(player_map_);
}

bool bship::BattleBoard::checkShipPlacement(const Ship& ship, const std::vector<std::vector<int>>& map)
{
	int shipLen = shipLengthMap.at(ship.name);

	bool validPlacement = true;
	int x = ship.row;
	int y = ship.col;
	for (int i = 0; i < shipLen; i++)
	{

		if(x < 0 || x > 9){
			validPlacement = false;
			break;
		}
		if(y < 0 || y > 9){
			validPlacement = false;
			break;
		}

		if (map[x][y] != Unknown) {
			validPlacement = false;
			break;
		}

		if (ship.direction == Right) {
			x++;
		} else {
			y++;
		}
	}
	return validPlacement;
}

bool bship::BattleBoard::checkGridLocation(
  int row, int col, HitStatus& status, bool& didSinkShip, ShipName& shipName)
{
	if (player_map_[row][col] == Hit) {
		status = Hit;
		int shipIndex = reverseIndexLookup_[(row*10+col)];
		ships_[shipIndex].hits++;
		if(checkIfSunk(ships_[shipIndex])){
			didSinkShip = true;
			shipName = ships_[shipIndex].name;
		}else{
			didSinkShip = false;
		}
	} else {
		status = Miss;
		didSinkShip = false;
	}

	return true;
}

void bship::BattleBoard::generateRandomValidShipPosition(Ship& ship)
{
	bool validPositionFound = false;
	while (!validPositionFound)
	{

		int rc = rand() % 100; // between 0 and 99
		int dir = rand() % 2;  // between 0 and 1
		ship.row = rc % 10;
		ship.col = rc / 10;
		if (dir == 1) {
			ship.direction = Right;
		} else {
			ship.direction = Down;
		}

		validPositionFound = checkShipPlacement(ship, player_map_);
	}

}

void bship::BattleBoard::generateRandomShips()
{
	srand (time(NULL));
	Ship newShip;
	newShip.name = Carrier;
	generateRandomValidShipPosition(newShip);
	ships_.push_back(newShip);
	placeShip(newShip, player_map_, ships_.size()-1);
	printShipDetails(newShip);

	newShip.name = Battleship;
	generateRandomValidShipPosition(newShip);
	ships_.push_back(newShip);
	placeShip(newShip, player_map_, ships_.size()-1);
	printShipDetails(newShip);

	newShip.name = Cruiser;
	generateRandomValidShipPosition(newShip);
	ships_.push_back(newShip);
	placeShip(newShip, player_map_, ships_.size()-1);
	printShipDetails(newShip);

	newShip.name = Submarine;
	generateRandomValidShipPosition(newShip);
	ships_.push_back(newShip);
	placeShip(newShip, player_map_, ships_.size()-1);
	printShipDetails(newShip);

	newShip.name = Destroyer;
	generateRandomValidShipPosition(newShip);
	ships_.push_back(newShip);
	placeShip(newShip, player_map_, ships_.size()-1);
	printShipDetails(newShip);
}

void bship::BattleBoard::printShipDetails(const Ship& ship)
{
	std::cout << "Ship: "
		<< shipNameLookup.at(ship.name) << " state: ("
		<< ship.row << ", " << ship.col << ", " << static_cast<int>(ship.direction)
		<< ")\n";
}

void bship::BattleBoard::placeShip(const Ship& ship, std::vector<std::vector<int>>& map, int shipIndex)
{
	if(!checkShipPlacement(ship, map)) { std::cerr << "Error placing ship!\n";}

	int shipLen = shipLengthMap.at(ship.name);

	int x = ship.row;
	int y = ship.col;
	for (int i = 0; i < shipLen; i++)
	{
		map[x][y] = Hit;
		reverseIndexLookup_[x*10+y] = shipIndex;

		if (ship.direction == Right) {
			x++;
		} else {
			y++;
		}
	}
}

void bship::BattleBoard::consolePrintBoard(const std::vector<std::vector<int>>& map)
{
	for(int i = 0; i < map.size(); i++)
	{
		for(int j = 0; j < map[i].size(); j++)
		{
			std::cout << map[i][j] << ", ";
		}
		std::cout << "\n";
	}
}

bool bship::BattleBoard::checkIfSunk(Ship& ship)
{
	std::cout << "Checking...\n";
	printShipDetails(ship);
	std::cout << "  has " << ship.hits << " hits \n\n";
	int shipLen = shipLengthMap.at(ship.name);
	if(shipLen <= ship.hits)
	{
		return true;
	}else{
		return false;
	}

}