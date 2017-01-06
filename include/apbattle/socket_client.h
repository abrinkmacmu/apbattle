#ifndef __socket__client__
#define __socket__client__

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <string>

namespace bship {
struct Client
{
    boost::asio::io_service svc;
    boost::asio::io_service& io_service;
    boost::asio::ip::tcp::socket socket;

    Client(std::string host, std::string port)
        : svc(), io_service(svc), socket(io_service)
    {
        ;
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query(host, port);
        boost::asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(query);

        std::cout << "Connecting to " << query.host_name() << " ...\n";
        boost::asio::connect(this->socket, endpoint);
    };

    void send(std::string const& message) {
        socket.send(boost::asio::buffer(message));
    }

    void printResponse() {
        for (;;)
        {
            boost::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            std::cout.write(buf.data(), len);

        }
    }
}; // class
} // ns bship

#endif