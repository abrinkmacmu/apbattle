#ifndef __socket__connection__
#define __socket__connection__

#include <iostream>
#include <queue>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <string>
#include <unistd.h> // usleep
#include <mutex>
#include <thread>

namespace bship{


	/*void asyncReadThread( std::queue<std::string> *queue, std::mutex *mu, 
		boost::asio::ip::tcp::socket *socket){

		for (;;)
		{
			boost::array<char, 128> buf;
			boost::system::error_code error;

			size_t len = socket->async_read_some(boost::asio::buffer(buf), error);
			if (error == boost::asio::error::eof) {
				break; // Connection closed cleanly by peer.
			} else if (error) {
				throw boost::system::system_error(error); // Some other error.
			}

			// insert message cleanly into queue
			mu->lock();
			queue->emplace(buf.data());
			mu->unlock();
		}

	}
	*/

	
	class SocketConnection{
	public:
		SocketConnection(std::string host, unsigned short port, bool isHost);

		bool read(std::string& response);

		bool write(std::string message);

	private:

		void setupHostConnection();
		void setupClientConnection();

		bool isHost_;
		boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::tcp::endpoint endpoint;
  	std::string accumulated;
    //std::queue<std::string> threaded_read_queue_;
    //std::mutex read_mutex_;
    //std::thread thread;



	}; // class

} // ns bship

#endif
