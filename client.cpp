#include <iostream>
#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::tcp;

void client() {
    boost::asio::io_context io_context;
    tcp::socket socket(io_context);
    char message[1024];

    tcp::resolver resolver(io_context);
    auto endpoint = resolver.resolve("127.0.0.1", "5555");

    boost::asio::connect(socket, endpoint);
    std::cout << "Connected to server." << std::endl;

    boost::asio::write(socket, boost::asio::buffer("Message to server."));

    size_t length = boost::asio::read(socket, boost::asio::buffer(message, 20));
    std::cout << "Server reply: " << std::string(message, length) << std::endl;
}