#include <boost/asio.hpp>
//#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <string>

struct Client
{
    boost::asio::io_service& io_service;
    boost::asio::ip::tcp::socket socket;

    Client(boost::asio::io_service& svc, std::string const& host, std::string const& port)
        : io_service(svc), socket(io_service)
    {
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
};

/*void server_thread() {
    try
    {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT));

        {
            boost::asio::ip::tcp::socket socket(io_service);
            acceptor.accept(socket);

            boost::asio::streambuf sb;
            boost::system::error_code ec;
            while (boost::asio::read(socket, sb, ec)) {
                std::cout << "received: '" << &sb << "'\n";

                if (ec) {
                    std::cout << "status: " << ec.message() << "\n";
                    break;
                }
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
*/

int main(int argc, char *argv[]) {
    boost::asio::io_service svc;
    Client client(svc, argv[1], argv[2]);
    std::cout << "Connected.\n";
    std::string send_string(argv[3]);
    send_string.append("\n");
    client.send(send_string);
    std::cout << "Sent  " << argv[3] << "\n";
    client.printResponse();
}