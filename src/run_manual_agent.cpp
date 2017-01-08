#include <iostream>
#include <string>
#include <apbattle/manual_agent.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 5)
	{
		std::cout << "args: <hostIP> <hostport> <playerName> <isHost>\n";
		return 0;
	}

	bool isHost = false;
	if( 0 == std::string("true").compare(argv[4]))
	{
		isHost = true;
	}

	bship::ManualAgent Agent1(argv[1], atoi(argv[2]),argv[3],  isHost) ;
	if(isHost){
		usleep(1e6);

	}
	std::srand (time(NULL));
	Agent1.playGame(isHost);	

	return 0;
}