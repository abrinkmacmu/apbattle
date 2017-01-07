#ifndef __battle__board__
#define __battle__board__

#include <iostream>
#include <vector>
#include <map>
#include <apbattle/bship_common.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace bship {


class BattleBoard {
public:
	/**
	 * @brief default constructor
	 */
	BattleBoard(std::string window_title);

	virtual ~BattleBoard(){};

	/**
	 * @brief checks if the ship position is valid in provided map
	 */
	bool checkShipPlacement(const Ship& ship);

	void setHit(int row, int col, HitStatus hs);

	virtual void reset();

	bool checkGameoverCondition();

	/**
	* @brief Handle all keyboard and mouse events
	*/
	bool handleGUIEvents(bool& isNewClick, int& row, int& col);

	/**
	 * @brief updates plot window
	 */
	bool updateWindow();

	// Setters/getters

	void getMap(std::vector<std::vector<int>>& map) {map = map_;};

	void setEnableGraphics(bool enable){ enableGraphics_ = enable;};

	void consolePrintBoard();

	

protected:
	std::vector<ShipName> sunk_list_;
	std::vector<std::vector<int>> map_;
	sf::RenderWindow window_;
	sf::VertexArray vArray_;
	bool enableGraphics_;
	int nCells_;
	int displaySize_;
	int cellSize_;

	void updateHitMapGraphics();

	
	


}; // class
} // ns bship
#endif