#include <iostream>
#include <string>
#include <apbattle/counting_agent.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 7)
	{
		std::cout << "args: <hostIP> <hostport> <playerName> <isHost> <enableLogging> <inflationFactor>\n";
		return 0;
	}

	bool isHost = false;
	if( 0 == std::string("true").compare(argv[4]))
	{
		isHost = true;
	}

	bool enableLogging = false;
	if( 0 == std::string("true").compare(argv[5]))
	{
		enableLogging = true;
	}

	bship::CountingAgent Agent1(argv[1], atoi(argv[2]),argv[3],  isHost, enableLogging, atoi(argv[6])) ;
	if(isHost){
		usleep(1e6);

	}
	std::srand (time(NULL));
	Agent1.playGame(isHost);	

	return 0;
}