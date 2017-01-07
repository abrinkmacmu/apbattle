
#include <stdlib.h>
#include <apbattle/battle_board.h>
#include <apbattle/bship_common.h>
#include <time.h>

bship::BattleBoard::BattleBoard(std::string owner, std::string window_title):
	nCells_(10),
	map_(10, std::vector<int>(10, bship::Unknown)),
	owner_(owner),
	displaySize_(400),
	cellSize_(40),
	window_(sf::VideoMode(400, 400), window_title), 
	vArray_(sf::Quads, 400)
{
	std::cout << "initalized " << window_title << "\n";
	updateWindow();
	window_.setFramerateLimit(30); // only need to call once
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
	std::cout << "row: " << row << " col: " << col << "  map_size: " << map_.size() << ", " << map_[0].size() << "\n";
	if (map_[row][col] == Hit) {
		status = Hit;
		int shipIndex = reverseIndexLookup_[(row*10+col)]; // TODO refactor Battleboard for enemy and player configs!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		ships_[shipIndex].hits++;
		if(checkIfSunk(ships_[shipIndex])){
			didSinkShip = true;
			shipName = ships_[shipIndex].name;
		}else{
			didSinkShip = false;
			shipName = None;
		}
	} else {
		status = Miss;
		didSinkShip = false;
	}

	return true;
}

void bship::BattleBoard::setHit(int row, int col, HitStatus hs)
{
	map_[row][col] = hs;
}


void bship::BattleBoard::reset(){
	for (int i = 0 ; i < nCells_; i++){
		for (int j=0; j < nCells_; j++){
			map_[i][j] = bship::Unknown;
		}
	}
	ships_.clear();
	reverseIndexLookup_.clear();
	if(0 == owner_.compare("player")){
		generateRandomShips();
		consolePrintBoard();
	}

	updateHitMapGraphics();
	updateWindow();

}


bool bship::BattleBoard::handleGUIEvents(bool& isNewClick, int& row, int& col) {

	if (!window_.isOpen() ) {std::cerr << "Window is not open\n"; return false;}

	isNewClick = false;

	sf::Event event;
	while (window_.pollEvent(event))
	{
		switch (event.type)
		{

		case sf::Event::Closed:
			window_.close();
			return false;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				isNewClick = true;
				row = event.mouseButton.y / cellSize_;
				col = event.mouseButton.x / cellSize_;
			}

		default:
			break;


		}// Switch

	}// pollEvent
	return true;
}

bool bship::BattleBoard::updateWindow()
{
	updateHitMapGraphics();
	window_.clear();
	window_.draw(vArray_);
	window_.display();
	return true;
}

void bship::BattleBoard::updateHitMapGraphics()
{
	for (int i = 0; i < nCells_; i++)
	{
		for (int j = 0; j < nCells_ ; j++)
		{

			sf::Vertex* quad = &vArray_[(i + j * nCells_) * 4];
			quad[0].position = sf::Vector2f(i * cellSize_, j * cellSize_);
			quad[1].position = sf::Vector2f((i + 1) * cellSize_, j * cellSize_);
			quad[2].position = sf::Vector2f((i + 1) * cellSize_, (j + 1) * cellSize_);
			quad[3].position = sf::Vector2f((i) * cellSize_, (j + 1) * cellSize_);

			sf::Color cellColor;
			switch (map_[j][i]) {
			case bship::Miss:
				cellColor = sf::Color::White;
				break;

			case bship::Hit:
				cellColor = sf::Color::Red;
				break;

			case bship::Unknown:
				cellColor = sf::Color::Blue;
				break;
			}

			quad[0].color = sf::Color::Black; // hack so borders are more easily seen
			quad[1].color = cellColor;
			quad[2].color = cellColor;
			quad[3].color = cellColor;
		}
	}
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

		validPositionFound = checkShipPlacement(ship, map_);
	}

}

void bship::BattleBoard::generateRandomShips()
{
	srand (time(NULL));
	Ship newShip;
	newShip.name = Carrier;
	generateRandomValidShipPosition(newShip);
	ships_.push_back(newShip);
	placeShip(newShip, ships_.size()-1);
	printShipDetails(newShip);

	newShip.name = Battleship;
	generateRandomValidShipPosition(newShip);
	ships_.push_back(newShip);
	placeShip(newShip, ships_.size()-1);
	printShipDetails(newShip);

	newShip.name = Cruiser;
	generateRandomValidShipPosition(newShip);
	ships_.push_back(newShip);
	placeShip(newShip, ships_.size()-1);
	printShipDetails(newShip);

	newShip.name = Submarine;
	generateRandomValidShipPosition(newShip);
	ships_.push_back(newShip);
	placeShip(newShip, ships_.size()-1);
	printShipDetails(newShip);

	newShip.name = Destroyer;
	generateRandomValidShipPosition(newShip);
	ships_.push_back(newShip);
	placeShip(newShip, ships_.size()-1);
	printShipDetails(newShip);
}

void bship::BattleBoard::printShipDetails(const Ship& ship)
{
	std::cout << "Ship: "
		<< shipNameLookup.at(ship.name) << " state: ("
		<< ship.row << ", " << ship.col << ", " << static_cast<int>(ship.direction)
		<< ")\n";
}

void bship::BattleBoard::placeShip(const Ship& ship, int shipIndex)
{
	if(!checkShipPlacement(ship, map_)) { std::cerr << "Error placing ship!\n";}

	int shipLen = shipLengthMap.at(ship.name);

	int x = ship.row;
	int y = ship.col;
	for (int i = 0; i < shipLen; i++)
	{
		map_[x][y] = Hit;
		reverseIndexLookup_[x*10+y] = shipIndex;

		if (ship.direction == Right) {
			x++;
		} else {
			y++;
		}
	}
}

void bship::BattleBoard::consolePrintBoard()
{
	for(int i = 0; i < map_.size(); i++)
	{
		for(int j = 0; j < map_[i].size(); j++)
		{
			std::cout << map_[i][j] << ", ";
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