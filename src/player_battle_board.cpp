
#include <apbattle/player_battle_board.h>


bship::PlayerBattleBoard::PlayerBattleBoard(std::string window_title):
BattleBoard::BattleBoard(window_title)
{
	std::cout << "initalized PlayerBattleBoard\n";
}



bool bship::PlayerBattleBoard::checkGridLocation(
  int row, int col, HitStatus& status, ShipName& shipName)
{
	std::cout << "row: " << row << " col: " << col << "  map_size: " << map_.size() << ", " << map_[0].size() << "\n";
	shipName = bship::None;
	if (map_[row][col] == Hit) {
		status = Hit;
		std::cout << "recombined: " << (row * 10 + col) << "\n";
		int shipIndex = reverseIndexLookup_[(row * 10 + col)]; // TODO refactor Battleboard for enemy and player configs!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		ships_[shipIndex].hits++;
		if (checkIfSunk(ships_[shipIndex])) {
			
			shipName = ships_[shipIndex].name;
		}
	} else {
		status = Miss;
		
	}

	return true;
}



void bship::PlayerBattleBoard::printShipDetails(const Ship& ship)
{
	std::cout << "Ship: "
	          << shipNameLookup.at(ship.name) << " state: ("
	          << ship.row << ", " << ship.col << ", " << static_cast<int>(ship.direction)
	          << ")\n";
}




void bship::PlayerBattleBoard::reset()
{
	generateRandomShips();
	consolePrintBoard();
	ships_.clear();
	reverseIndexLookup_.clear();

	BattleBoard::reset();
}






void bship::PlayerBattleBoard::generateRandomShips()
{
	srand (time(NULL));
	Ship newShip;
	newShip.name = Carrier;
	generateRandomValidShipPosition(newShip);
	ships_.push_back(newShip);
	placeShip(newShip, ships_.size() - 1);
	printShipDetails(newShip);

	newShip.name = Battleship;
	generateRandomValidShipPosition(newShip);
	ships_.push_back(newShip);
	placeShip(newShip, ships_.size() - 1);
	printShipDetails(newShip);

	newShip.name = Cruiser;
	generateRandomValidShipPosition(newShip);
	ships_.push_back(newShip);
	placeShip(newShip, ships_.size() - 1);
	printShipDetails(newShip);

	newShip.name = Submarine;
	generateRandomValidShipPosition(newShip);
	ships_.push_back(newShip);
	placeShip(newShip, ships_.size() - 1);
	printShipDetails(newShip);

	newShip.name = Destroyer;
	generateRandomValidShipPosition(newShip);
	ships_.push_back(newShip);
	placeShip(newShip, ships_.size() - 1);
	printShipDetails(newShip);
}



void bship::PlayerBattleBoard::generateRandomValidShipPosition(Ship& ship)
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

		validPositionFound = checkShipPlacement(ship);
	}

}





void bship::PlayerBattleBoard::placeShip(const Ship& ship, int shipIndex)
{
	if (!checkShipPlacement(ship)) { std::cerr << "Error placing ship!\n";}

	int shipLen = shipLengthMap.at(ship.name);

	int x = ship.row;
	int y = ship.col;
	for (int i = 0; i < shipLen; i++)
	{
		map_[x][y] = Hit;
		reverseIndexLookup_[x * 10 + y] = shipIndex;

		if (ship.direction == Right) {
			x++;
		} else {
			y++;
		}
	}
}



bool bship::PlayerBattleBoard::checkIfSunk(Ship& ship)
{
	std::cout << "Checking...\n";
	printShipDetails(ship);
	std::cout << "  has " << ship.hits << " hits \n\n";
	int shipLen = shipLengthMap.at(ship.name);
	if (shipLen <= ship.hits)
	{
		return true;
	} else {
		return false;
	}

}



