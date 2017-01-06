#ifndef __bship__common__
#define __bship__common__

#include <cereal/archives/json.hpp>
#include <sstream>
#include <map>


namespace bship {

enum HitStatus {
	Unknown,
	Hit,
	Miss
};

const std::map<HitStatus, std::string> hitStatusLookup{
	{Unknown, ""},
	{Hit, "Hit!"},
	{Miss, "Miss!"}
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
	Destroyer,
	None
};

const std::map<ShipName, int> shipLengthMap{
	{Carrier, 5},
	{Battleship, 4},
	{Cruiser, 3},
	{Submarine, 3},
	{Destroyer, 2},
	{None, 0}
};

const std::map<ShipName, std::string> shipNameLookup{
	{Carrier, "Carrier"},
	{Battleship, "Battleship"},
	{Cruiser, "Crusier"},
	{Submarine, "Submarine"},
	{Destroyer, "Destroyer"},
	{None, ""}
};

inline std::string createGuessMsg(int guess) {

	std::stringstream ss;
	{
		cereal::JSONOutputArchive archive(ss);
		archive(CEREAL_NVP(guess));
	}
	return ss.str();

};

inline std::string createResponseMsg(HitStatus hitStatus, ShipName sunkShip, bool gameover)
{

	std::string response(hitStatusLookup.at(hitStatus));
	std::string sunk(shipNameLookup.at(sunkShip));

	std::stringstream ss;
	{
		cereal::JSONOutputArchive archive(ss);
		archive(CEREAL_NVP(response),
		        CEREAL_NVP(sunk),
		        CEREAL_NVP(gameover));
	}
	return ss.str();
};

inline std::string createConnectionMsg(bool reset_requested, bool ready_to_play) {
	std::stringstream ss;
	{
		cereal::JSONOutputArchive archive(ss);
		archive(CEREAL_NVP(reset_requested),
		        CEREAL_NVP(ready_to_play));
	}
	return ss.str();
};

struct Ship {
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