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



inline void removeNewLine(std::string &s)
{
	for (;;) {
		auto it = s.find('\n');
		if ( it != s.npos) {
			s.erase(it, 1);
		} else {
			return;
		}
	}
};

struct ConnectionMsg {
	int message_type = 0;
	bool reset_requested;
	bool ready_to_play;
	template<class Archive>
	void serialize(Archive &archive){
		archive(message_type, reset_requested, ready_to_play);
	}
};

struct GuessMsg {
	int message_type = 1;
	int guess;
	template<class Archive>
	void serialize(Archive &archive){
		archive(message_type, guess);
	}
};

struct ResponseMsg {
	int message_type = 2;
	std::string response;
	std::string sunk;
	bool gameover;
	template<class Archive>
	void serialize(Archive &archive){
		archive(message_type, response, sunk, gameover);
	}
};

inline std::string createGuessMsg(int guess) {
	int message_type = 1;
	std::stringstream ss;
	{
		cereal::JSONOutputArchive archive(ss);
		archive(CEREAL_NVP(message_type),
		        CEREAL_NVP(guess));
	}
	std::string str(ss.str());
	removeNewLine(str);
	return str;

};



inline std::string createResponseMsg(HitStatus hitStatus, ShipName sunkShip, bool gameover)
{

	std::string response(hitStatusLookup.at(hitStatus));
	std::string sunk(shipNameLookup.at(sunkShip));
	int message_type = 2;

	std::stringstream ss;
	{
		cereal::JSONOutputArchive archive(ss);
		archive(CEREAL_NVP(message_type),
		        CEREAL_NVP(response),
		        CEREAL_NVP(sunk),
		        CEREAL_NVP(gameover));
	}

	std::string str(ss.str());
	removeNewLine(str);
	return str;
};

//inline cereal::JSONInputArchive decodeMessage(std::string msg){
//	std::stringstream(msg);
//	{
//	cereal::JSONInputArchive(ss);
//}

inline std::string createConnectionMsg(bool reset_requested, bool ready_to_play) {
	std::stringstream ss;
	int message_type = 0;
	{
		cereal::JSONOutputArchive archive(ss);
		archive(CEREAL_NVP(message_type),
		        CEREAL_NVP(reset_requested),
		        CEREAL_NVP(ready_to_play));
	}
	std::string str(ss.str());
	removeNewLine(str);
	return str;
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