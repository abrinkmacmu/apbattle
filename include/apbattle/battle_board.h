#ifndef __battle__board__
#define __battle__board__

#include <iostream>
#include <vector>
#include <map>
#include <apbattle/bship_common.h>

namespace bship{


	class BattleBoard {
	public:
		/**
		 * @brief default constructor
		 */
		BattleBoard();

		/**
		 * @brief checks if the ship position is valid in provided map
		 */
		bool checkShipPlacement(const Ship& ship, const std::vector<std::vector<int>>& map);

		/**
		 * @brief Checks player's map for HitStatus and sinking status
		 */
		bool checkGridLocation(int row, int col, HitStatus& status, bool& didSinkShip, ShipName& shipName);

		void getEnemyMap(std::vector<std::vector<int>>& map){map = enemy_map_;};
		void getPlayerMap(std::vector<std::vector<int>>& map){map = player_map_;};

		std::vector<Ship> getShipLocations(){return ships_;};

	private:
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
		void placeShip(const Ship& ship, std::vector<std::vector<int>>& map, int shipIndex);

		void consolePrintBoard(const std::vector<std::vector<int>>& map);

		bool checkIfSunk(Ship& ship);

		std::vector<Ship> ships_;
		std::vector<std::vector<int>> enemy_map_;
		std::vector<std::vector<int>> player_map_;
		std::map<int, int> reverseIndexLookup_;


	}; // class
} // ns bship
#endif