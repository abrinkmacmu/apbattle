
#ifndef __socket__server__
#define __socket__server__

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <string>
#include <unistd.h> // usleep

namespace bship {

void asyncReadServer( std::queue<std::string> *queue, std::mutex *mu, 
                     std::string host, unsigned short port)
{
	try {
		boost::asio::io_service io_service;

		//tcp::endpoint end_point(boost::asio::ip::address_v4(0x7F000001), 8080); //127.0.0.1
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::from_string(host), port);
		std::cout << "Created enpoint at " << endpoint.address() << " : " << endpoint.port() << "\n";
		boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);

		boost::asio::ip::tcp::socket socket(io_service);
		std::cout << "Created acceptor, waiting for new connection... \n";
		acceptor.accept(socket);
		std::cout << "Connected. Preparing to receive messages now. \n";

		for (;;)
		{
			boost::array<char, 128> buf;
			boost::system::error_code error;

			size_t len = socket.read_some(boost::asio::buffer(buf), error);
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

	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return;

}

} // ns bship

#endif