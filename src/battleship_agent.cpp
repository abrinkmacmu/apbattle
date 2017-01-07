
#include <iostream>
#include <unistd.h> //sleep
#include <queue>
#include <apbattle/bship_common.h>
#include <apbattle/battleship_agent.h>

#include <cereal/external/rapidjson/document.h>


bship::BattleshipAgent::BattleshipAgent(
  std::string host, unsigned short port,
  std::string playerName, bool isHost):
	socketConnection_(host, port, isHost),
	host_(host),
	port_(port)
{

	std::cout << "Battleship Agent successfully constructed\n";

	if (isHost) {

		socketConnection_.write(createResponseMsg(bship::Hit, bship::Carrier, false));
		usleep(1e6);
	} else {

		std::string read_buffer;
		bool suc = true;
		for (;;) {
			suc = socketConnection_.read(read_buffer);

			std::cout << "raw read message: " << read_buffer << "nl\n";
			// deserialize class
			bship::GuessMsg newGuess;
			rapidjson::Document document;
			document.Parse(read_buffer.c_str());

			std::cout << "deserialized data is : " 
				<< document["message_type"].GetInt() << ","
				<< document["response"].GetString() << ","
				<< document["sunk"].GetString() << ","
				<< document["gameover"].GetBool() << "\n";


			if ( suc) {
				std::cout << read_buffer << "\n";
				socketConnection_.write(read_buffer.append(playerName));
				usleep(1e6);

			} else {
				std::cout << "failed to read buffer\n";
				usleep(1e6);
			}

		}
	}

}

bship::BattleshipAgent::~BattleshipAgent()
{


}

void bship::BattleshipAgent::playGame()
{

}


void bship::BattleshipAgent::guessLocation()
{

}

void bship::BattleshipAgent::respondToRequest()
{

}

void bship::BattleshipAgent::logMoves()
{

}





