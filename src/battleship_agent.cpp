
#include <iostream>
#include <unistd.h>
#include <queue>
#include <apbattle/battleship_agent.h>
#include <mutex>
#include <thread>


namespace bship{

std::mutex reader_mutex;
void asyncReadServer( std::queue<std::string> *queue,
    std::string host, std::string port)
{
	
	std::string str("Hello");
	int n = 0;
	for (;;) {
		std::string str("Hello ");
		str.append(std::to_string(n));
		reader_mutex.lock();
		queue->emplace(str);
		reader_mutex.unlock();
		n++;
		usleep(1e6);
		if(n > 10){ break;}
	}

}

} // ns bship

bship::BattleshipAgent::BattleshipAgent(
    std::string host, std::string host_port,
    std::string client, std::string client_port):
    	socketClient_( client, client_port){

	//future_read_queue_ = std::async(std::launch::async, asyncReadServer, host, host_port);
	//std::cout << "Started up async reader\n";
    //std::queue<std::string> read_queue = future_read_queue_.get();

    std::queue<std::string> read_queue;
    std::thread t(&bship::asyncReadServer, &read_queue, host, host_port);


	for(;;){
		usleep(3e6);
		std::cout << "slept, waiting for queue result\n";
		reader_mutex.lock();
		
		while(!read_queue.empty())
		{
			std::cout << read_queue.front() << "\n";

			read_queue.pop();
		}
		reader_mutex.unlock();
	}


}

bship::BattleshipAgent::~BattleshipAgent()
{


}

void bship::BattleshipAgent::playGame()
{

}


void bship::BattleshipAgent::connectToSocket()
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

void bship::BattleshipAgent::sendMessage()
{

}

