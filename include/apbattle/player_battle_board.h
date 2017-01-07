#ifndef __player_battle_board__
#define __player_battle_board__

#include <apbattle/battle_board.h>


namespace bship {

class PlayerBattleBoard: public BattleBoard {
public:


	PlayerBattleBoard(std::string window_title);

	/**
	 * @brief Checks player's map for HitStatus and sinking status
	 */
	bool checkGridLocation(int row, int col, HitStatus& status, ShipName& shipName);

	/**
	 * @brief helper to print details for debugging
	 */
	void printShipDetails(const Ship& ship);

	std::vector<Ship> getShipLocations() {return ships_;}

	void reset();

private:
	std::vector<Ship> ships_;
	std::map<int, int> reverseIndexLookup_;

	/**
		 * @brief generates a random, valid ship configurations for all ships
		 */
	void generateRandomShips();

	/**
	 * @brief self-explainatory
	 */
	void generateRandomValidShipPosition(Ship& ship);

	/**
	 * @brief places specified ship onto the hit_map
	 */
	void placeShip(const Ship& ship, int shipIndex);

	bool checkIfSunk(Ship& ship);

}; // class

} // ns

#endif