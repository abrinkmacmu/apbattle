#ifndef __battle__board__
#define __battle__board__

#include <iostream>
#include <vector>
#include <map>

namespace bship{

	enum Direction{
		Down,
		Right
	};

	enum ShipName{
		Carrier,
		Battleship,
		Cruiser,
		Submarine,
		Destroyer
	};

	const std::map<ShipName, int> shipLengthMap{
		{Carrier, 5},
		{Battleship, 4},
		{Cruiser, 3},
		{Submarine, 3}, 
		{Destroyer, 2},
	};


	struct Ship{
		ShipName name;
		int row;
		int col;
		Direction direction;

		void setPos(int r, int c, Direction dir)
		{
			row = r;
			col = c;
			direction = dir;
		}

		void setAll(ShipName n, int r, int c, Direction dir)
		{
			name = n;
			setPos(r, c, dir);
		}

	}; // struct Ship

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
		bool checkGridLocation(HitStatus& status, bool& didSinkShip, ShipName& shipName);

		void getEnemyMap(std::vector<std::vector<int>>& map){map = enemy_map_;};
		void getPlayerMap(std::vector<std::vector<int>>& map){map = player_map_;};

	private:
		/**
		 * @brief self-explainatory
		 */
		void generateRandomValidShipPosition(Ship& ship);

		/**
		 * @brief generates a random, valid ship configurations for all ships
		 */
		void generateRandomShips();


		std::vector<Ship> ships_;
		std::vector<std::vector<int>> enemy_map_;
		std::vector<std::vector<int>> player_map_;


	}; // class
} // ns bship
#endif