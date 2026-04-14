#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <ctime>

using boost::asio::ip::tcp;

int randomElo() {
    srand(time(0));
    int random = (rand() % 2001) + 100;
    return random;
}

void client() {
    boost::asio::io_context io_context;
    tcp::socket socket(io_context);
    char message[1024];

    int elo = randomElo();
    std::cout << "Your elo is: " << elo << std::endl;

    tcp::resolver resolver(io_context);
    auto endpoint = resolver.resolve("127.0.0.1", "5555");

    boost::asio::connect(socket, endpoint);
    std::cout << "Connected to server." << std::endl;

    boost::asio::write(socket, boost::asio::buffer("Message to server."));

    size_t length = socket.read_some(boost::asio::buffer(message));
    std::cout << "Server reply: " << std::string(message, length) << std::endl;
}