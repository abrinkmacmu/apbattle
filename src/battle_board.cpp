#include <apbattle/battle_board.h>

bship::BattleBoard::BattleBoard():
	enemy_map_(10, std::vector<int>(10, Unknown)),
	player_map_(10, std::vector<int>(10, Unknown))
{
	generateRandomShips();
}

bool checkShipPlacement(const Ship& ship, const std::vector<std::vector<int>>& map)
{
	;
}

bool checkGridLocation(HitStatus& status, bool& didSinkShip, ShipName& shipName)
{
	;
}

void generateRandomValidShipPosition(Ship& ship)
{
	;
}

void generateRandomShips()
{
	;
}