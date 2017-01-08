#include <apbattle/socket_connection.h>


bship::SocketConnection::SocketConnection(std::string host, unsigned short port, bool isHost):
	io_service(), socket(io_service), accumulated()
{
	std::cout << "in SocketConnection ctor\n";
	endpoint = boost::asio::ip::tcp::endpoint (boost::asio::ip::address_v4::from_string(host), port);

	std::cout << "Connecting at " << endpoint.address() << " : " << endpoint.port() << "\n";

	if (isHost)
	{
		setupHostConnection();
	} else {
		setupClientConnection();
	}

	//thread = std::thread(&asyncReadThread, &threaded_read_queue_, &read_mutex_, &socket);


}

void bship::SocketConnection::setupHostConnection()
{
	std::cout << "Hosting... waiting for clients to connect\n";
	boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);
	acceptor.accept(socket);
	std::cout << "Client Accepted.\n";
	accumulated.clear();
}

void bship::SocketConnection::setupClientConnection()
{
	std::cout << "A Client... attempting to connect to host\n";
	int attempts = 0;
	bool connected = false;
	while (attempts < 50) {

		boost::system::error_code ec;
		socket.connect(endpoint, ec);
		if (ec) {
			std::cout << "attempt " << attempts << " failed, retrying..\n";
			attempts++;
			usleep(2e6);
		} else {
			connected = true;
			break;
		}
	}
	if (connected) {
		std::cout << "Client successfully connected to host\n";
	} else {
		std::cerr << "ERROR: Client could not reach host, giving up\n";
	}
	accumulated.clear();
}

bool bship::SocketConnection::read(std::string& read_buffer)
{
	for (;;) {
		boost::array<char, 128> buf;
		boost::system::error_code error;

		size_t len = socket.read_some(boost::asio::buffer(buf), error);

		if (error == boost::asio::error::eof) {
			return false;
		}	else if (error) {
			throw boost::system::system_error(error); // Some other error.
			return false;
		}

		// had some copy issues that this fixed
		// bad unicode characters likely due to fixed-size buf array were 
		// being copied into the json string
		std::copy(buf.begin(), buf.begin() + len, std::back_inserter(accumulated));

		auto first = accumulated.find('\n');
		if ( first != accumulated.npos) {
			read_buffer = accumulated.substr(0, first);
			accumulated.erase(accumulated.begin(), accumulated.begin() + first + 1);



			return true;
		}
	}
}

bool bship::SocketConnection::write(std::string message)
{
	socket.send(boost::asio::buffer(message.append("\n")));
}