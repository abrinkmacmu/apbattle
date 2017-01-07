#include <apbattle/enemy_battle_board.h>

bship::EnemyBattleBoard::EnemyBattleBoard(std::string window_title):
BattleBoard::BattleBoard(window_title)
{
	std::cout << "Initiated Enemy derived class\n";
}