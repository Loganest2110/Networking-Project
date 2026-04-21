#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <ctime>

using boost::asio::ip::tcp;

// Function for generating random elo between 100 and 2000
int randomElo() {
    int random = (rand() % 1901) + 100;
    return random;
}

void client() {
    srand(time(0));

    // Variables for later
    boost::asio::io_context io_context;
    tcp::socket socket(io_context);
    char message[1024];

    // Elo generation
    int elo = randomElo();
    std::cout << "Your elo is: " << elo << std::endl;
    std::string eloString = std::to_string(elo);

    // Connecting to the server
    tcp::resolver resolver(io_context);
    auto endpoint = resolver.resolve("127.0.0.1", "5555");
    boost::asio::connect(socket, endpoint);
    std::cout << "Connected to server." << std::endl;

    // Writing a message to server and receiving a response
    boost::asio::write(socket, boost::asio::buffer(eloString));
    size_t length = socket.read_some(boost::asio::buffer(message));
    std::cout << std::string(message, length) << std::endl;
}