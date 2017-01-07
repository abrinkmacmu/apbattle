#ifndef __bship__common__
#define __bship__common__

#include <cereal/archives/json.hpp>
#include <cereal/external/rapidjson/document.h>
#include <cassert>
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
	{Cruiser, "Cruiser"},
	{Submarine, "Submarine"},
	{Destroyer, "Destroyer"},
	{None, ""}
};

const std::map<std::string, ShipName> shipNameReverseLookup{
	{"Carrier", Carrier},
	{"Battleship", Battleship},
	{"Cruiser", Cruiser},
	{"Submarine", Submarine},
	{"Destroyer", Destroyer},
	{"", None}
};

const int CONNECTION_CONST = 0;
const int GUESS_CONST = 1;
const int RESPONSE_CONST = 2;


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

inline void parseConnectionMsg(std::string& msg, bool& reset_requested, bool& ready_to_play)
{
	rapidjson::Document document;
	document.Parse(msg.c_str());

	assert(document["message_type"].GetInt() == CONNECTION_CONST);

	reset_requested = document["reset_requested"].GetBool();
	ready_to_play = document["ready_to_play"].GetBool();
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

inline void parseGuessMsg(std::string& msg, int& guess)
{
	rapidjson::Document document;
	document.Parse(msg.c_str());

	assert(document["message_type"].GetInt() == GUESS_CONST);

	guess = document["guess"].GetInt();
};



inline std::string createResponseMsg(HitStatus hitStatus, ShipName sunkShip, bool gameover)
{

	std::string response(hitStatusLookup.at(hitStatus));
	std::cout << "found response: " << response << "\n";
	std::string sunk(shipNameLookup.at(sunkShip));
	std::cout << "found sunk: " << sunk << "\n";
	int message_type = RESPONSE_CONST;

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

inline void parseResponseMsg(std::string msg, HitStatus& response, ShipName& sunk, bool& gameover)
{
	rapidjson::Document document;
	document.Parse(msg.c_str());

	assert(document["message_type"].GetInt() == RESPONSE_CONST);

	std::string res_string(document["response"].GetString());

	if( 0 == res_string.compare("Hit!")){
		response = Hit;
	}else if( 0 == res_string.compare("Miss!")){
		response = Miss;
	}else{
		std::cerr << "Error: Response:Response type unknown \n";
	}

	sunk = shipNameReverseLookup.at(document["sunk"].GetString());

	gameover = document["gameover"].GetBool();
	         
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