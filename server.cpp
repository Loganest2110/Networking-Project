#include <iostream>
#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::tcp;

void server() {
    boost::asio::io_context io_context;
    tcp::socket socket(io_context);
    char message[1024];

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 5555));
    std::cout << "Server successfully started." << std::endl;

    acceptor.accept(socket);
    std::cout << "Connected to client." << std::endl;

    size_t length = socket.read_some(boost::asio::buffer(message));
    std::cout << "Message: " << std::string(message, length) << std::endl;

    boost::asio::write(socket, boost::asio::buffer("Server response."));
}