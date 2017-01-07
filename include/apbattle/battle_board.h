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
	BattleBoard(std::string owner, std::string window_title);

	/**
	 * @brief checks if the ship position is valid in provided map
	 */
	bool checkShipPlacement(const Ship& ship, const std::vector<std::vector<int>>& map);

	/**
	 * @brief Checks player's map for HitStatus and sinking status
	 */
	bool checkGridLocation(int row, int col, HitStatus& status, bool& didSinkShip, ShipName& shipName);

	void setHit(int row, int col, HitStatus hs);

	void getMap(std::vector<std::vector<int>>& map) {map = map_;};

	std::vector<Ship> getShipLocations() {return ships_;};

	void reset();

	/**
	* @brief Handle all keyboard and mouse events
	*/
	bool handleGUIEvents(bool& isNewClick, int& row, int& col);

	/**
	 * @brief updates plot window
	 */
	bool updateWindow();

private:

	void updateHitMapGraphics();

	/**
	 * @brief self-explainatory
	 */
	void generateRandomValidShipPosition(Ship& ship);

	/**
	 * @brief generates a random, valid ship configurations for all ships
	 */
	void generateRandomShips();

	/**
	 * @brief helper to print details for debugging
	 */
	void printShipDetails(const Ship& ship);

	/**
	 * @brief places specified ship onto the hit_map
	 */
	void placeShip(const Ship& ship, int shipIndex);

	void consolePrintBoard();

	bool checkIfSunk(Ship& ship);

	std::vector<Ship> ships_;
	std::vector<std::vector<int>> map_;
	std::map<int, int> reverseIndexLookup_;
	std::string owner_;
	int nCells_;
	int cellSize_;
	int displaySize_;
	sf::RenderWindow window_;
	sf::VertexArray vArray_;


}; // class
} // ns bship
#endif