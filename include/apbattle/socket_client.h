#ifndef __socket__client__
#define __socket__client__

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <string>
#include <unistd.h> // usleep

namespace bship {
struct Client
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::tcp::endpoint endpoint;

    Client():
        io_service(), socket(io_service)
    {

    }

    bool connect(std::string host, unsigned short port) {
        endpoint = boost::asio::ip::tcp::endpoint (boost::asio::ip::address_v4::from_string(host), port);
        std::cout << "Client connecting at " << endpoint.address() << " : " << endpoint.port() << "\n";
        int attempts = 0;
        while (attempts < 10) {

            boost::system::error_code ec;
            socket.connect(endpoint, ec);
            if (ec) {
                std::cout << "attempt " << attempts << " failed, retrying..\n";
                attempts++;
                usleep(2e6);

            } else {
                return true;
            }
        }
        return false;
    };

    void send(std::string const& message) {
        socket.send(boost::asio::buffer(message));
    };

}; // class
} // ns bship

#endif