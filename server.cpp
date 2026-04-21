#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include "matchmaker.h"

using boost::asio::ip::tcp;

class Server {
private:
    tcp::acceptor acceptor;
    Matchmaker matchmaker;

    void acceptClients() {
        acceptor.async_accept([this](boost::system::error_code error, tcp::socket socket) {
            if (!error) {
                std::cout << "Client connected to server" << std::endl;

                char data[1024];
                size_t length = socket.read_some(boost::asio::buffer(data));

                int playerElo = std::stoi(std::string(data, length));
                matchmaker.addPlayer(std::move(socket), playerElo);
            }
            acceptClients();
        });
    }

public:
    Server(boost::asio::io_context& io_context, short port) : acceptor(io_context, tcp::endpoint(tcp::v4(), port)),
    matchmaker(io_context) {
        std::cout << "Server started and can except clients." << std::endl;
        acceptClients();
    }
};

int main() {
    boost::asio::io_context io_context;
    Server server(io_context, 5555);
    io_context.run();
}