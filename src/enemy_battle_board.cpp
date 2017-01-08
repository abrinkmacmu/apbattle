#include <apbattle/enemy_battle_board.h>
#include <algorithm>

bship::EnemyBattleBoard::EnemyBattleBoard(std::string window_title)
	:
	BattleBoard::BattleBoard(window_title)
{

}

void bship::EnemyBattleBoard::setInflation(int inflation){
	inflationFactor_ = inflation;
}

void bship::EnemyBattleBoard::computeProbabilityDistribution(int& bestRow, int& bestCol)
{
	std::vector<std::vector<int>> count_map(10, std::vector<int>(10, 0));

	std::vector<ShipName> all_ships = {Carrier, Battleship, Cruiser, Submarine, Destroyer};

	// Compute the count_map_ for all un-sunk ships

	for (auto it_sn = all_ships.begin(); it_sn != all_ships.end(); it_sn++)
	{

		auto found_it = std::find(sunk_list_.begin(), sunk_list_.end(), *it_sn);
		if (found_it != sunk_list_.end()) {
			// ship is sunk
			//std::cout << "Not counting: " << shipNameLookup.at(*it_sn);
			continue;
		}
		//std::cout << "Ship: " << shipNameLookup.at(*it_sn) << " is not sunk, counting placements\n";

		bruteForceCount(*it_sn, count_map);
	}

	// Also add inflation counts for hit locations
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if(map_[i][j] == bship::Hit){
				if( (i-1) >= 0){ count_map[i-1][j] += inflationFactor_;}
				if( (i+1) <= 9){ count_map[i+1][j] += inflationFactor_;}
				if( (j-1) >= 0){ count_map[i][j-1] += inflationFactor_;}
				if( (j+1) <= 9){ count_map[i][j+1] += inflationFactor_;}
			}
		}
	}

	// now find the best row/col coordinate
	int bestValue = -1;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
		{
			if (count_map[i][j] > bestValue and map_[i][j] == Unknown) {
				bestValue = count_map[i][j];
				bestRow = i;
				bestCol = j;
			}
		}
	}

	return;
}

void bship::EnemyBattleBoard::bruteForceCount(
  ShipName sn, std::vector<std::vector<int>>& count_map)
{
	bship::Ship thisShip;
	int len = shipLengthMap.at(sn)-2;
	for (int i = 0; i < (10); i++) // minor efficiency gain for upper bound
	{
		for (int j = 0; j < (10); j++)
		{
			thisShip.setAll(sn, i, j, Down);
			if (checkShipPlacement(thisShip) ) {
				appendShipCounts(thisShip, count_map);
			}

			thisShip.setAll(sn, i, j, Right);
			if (checkShipPlacement(thisShip) ) {
				appendShipCounts(thisShip, count_map);
			}

		}
	}

}


void bship::EnemyBattleBoard::appendShipCounts(
  const Ship& ship, std::vector<std::vector<int>>& count_map)
{
	int shipLen = shipLengthMap.at(ship.name);

	int x = ship.row;
	int y = ship.col;
	for (int i = 0; i < shipLen; i++)
	{
		count_map[x][y] += 1;
		if (ship.direction == Right) {
			x++;
		} else {
			y++;
		}
	}
	return;
}