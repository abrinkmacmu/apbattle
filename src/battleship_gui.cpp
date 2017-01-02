#include <apbattle/battleship_gui.h>
#include <iostream>

bship::BattleshipGui::BattleshipGui():
	nCells_(10),
	displaySize_(400),
	cellSize_(displaySize_ / nCells_),
	hit_map_(nCells_, std::vector<int>(nCells_, bship::Unknown)),
	window_(sf::VideoMode(displaySize_, displaySize_), "Battleship"),
	vArray_(sf::Quads, 4 * nCells_ * nCells_)
{
	window_.setFramerateLimit(30); // only need to call once
}

bool bship::BattleshipGui::handleEvents(bool& isNewClick, int& row, int& col) {

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
				row = event.mouseButton.x / cellSize_;
				col = event.mouseButton.y / cellSize_;
			}

		default:
			break;


		}// Switch

	}// pollEvent
	return true;
}

bool bship::BattleshipGui::updateWindow()
{
	updateHitMapGraphics();
	window_.clear();
	window_.draw(vArray_);
	window_.display();
	return true;
}

bool bship::BattleshipGui::setHit(int row, int col, bship::HitStatus status)
{
	if (hit_map_[row][col] != bship::Unknown) {
		std::cout << "Warning: changing assigned hit-map value\n";
	}
	hit_map_[row][col] = status;
	return true;
}

void bship::BattleshipGui::updateHitMapGraphics()
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
			switch (hit_map_[i][j]) {
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