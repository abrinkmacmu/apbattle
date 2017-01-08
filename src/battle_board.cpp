
#include <stdlib.h>
#include <apbattle/battle_board.h>
#include <apbattle/bship_common.h>
#include <time.h>

bship::BattleBoard::BattleBoard(std::string window_title):
	map_(10, std::vector<int>(10, bship::Unknown)),
	window_(sf::VideoMode(400, 400), window_title), 
	vArray_(sf::Quads, 400)
{
	nCells_ = 10;
	displaySize_ = 400;
	cellSize_ = 40;

	updateWindow();
	window_.setFramerateLimit(30); // only need to call once
	std::cout << "initalized Base Battle Board: " << window_title << "\n";
}

bool bship::BattleBoard::checkShipPlacement(const Ship& ship)
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

		if (map_[x][y] != Unknown) {
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

void bship::BattleBoard::setHit(int row, int col, HitStatus hs)
{
	map_[row][col] = hs;
}

void bship::BattleBoard::setDeadCell(int row, int col)
{
	map_[row][col] = bship::SunkCell;
}

bool bship::BattleBoard::checkGameoverCondition()
{
	if(sunk_list_.size() >= 5 )
	{
		return true;
	}else{
		return false;
	}
}


void bship::BattleBoard::reset(){
	for (int i = 0 ; i < nCells_; i++){
		for (int j=0; j < nCells_; j++){
			map_[i][j] = bship::Unknown;
		}
	}
	sunk_list_.clear();
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


void bship::BattleBoard::updateHitMapGraphics()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10 ; j++)
		{

			sf::Vertex* quad = &vArray_[(i + j * 10) * 4];
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

			case bship::Placed:
				cellColor = sf::Color::Yellow;
				break;
			case bship::SunkCell:
				cellColor = sf::Color::Black;
				break;
			}

			quad[0].color = sf::Color::Black; // hack so borders are more easily seen
			quad[1].color = cellColor;
			quad[2].color = cellColor;
			quad[3].color = cellColor;
		}
	}
}