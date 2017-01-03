#ifndef __bship__common__
#define __bship__common__


namespace bship {

enum HitStatus {
	Unknown,
	Hit,
	Miss
};

enum Direction {
	Down,
	Right
};

enum ShipName {
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

const std::map<ShipName, std::string> shipNameLookup{
	{Carrier, "Carrier"},
	{Battleship, "Battleship"},
	{Cruiser, "Crusier"},
	{Submarine, "Submarine"},
	{Destroyer, "Destroyer"},
};

struct Ship{
		ShipName name;
		int row;
		int col;
		Direction direction;
		int hits = 0;

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

} // ns bship
#endif