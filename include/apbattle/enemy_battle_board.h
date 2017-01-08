#ifndef __enemy_battle_board__
#define __enemy_battle_board__

#include <apbattle/battle_board.h>
#include <apbattle/bship_common.h>


namespace bship {

class EnemyBattleBoard: public BattleBoard {

public:

	EnemyBattleBoard(std::string window_title);

	void setInflation(int inflation);

	void computeProbabilityDistribution(int& bestRow, int& bestCol);

private:

	void bruteForceCount(ShipName sn, std::vector<std::vector<int>>& count_map);

	void appendShipCounts(const Ship& ship, std::vector<std::vector<int>>& count_map);

	int inflationFactor_;

};

}

#endif