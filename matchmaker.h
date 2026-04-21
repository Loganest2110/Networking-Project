#pragma once
#include <boost/asio.hpp>
#include <vector>
#include <memory>
#include <chrono>
#include <iostream>
#include <cmath>

using boost::asio::ip::tcp;

struct Player {
    tcp::socket socket;
    int elo;
    std::chrono::steady_clock::time_point startTime;

    Player(tcp::socket socket, int elo) : socket(std::move(socket)), elo(elo), startTime(std::chrono::steady_clock::now()) {}
};

class Matchmaker {
private:
    std::vector<std::shared_ptr<Player>> queue;
    boost::asio::steady_timer timer;

    void startTimer() {
        timer.expires_after(std::chrono::seconds(1));
        timer.async_wait([this](const boost::system::error_code& error) {
            if (!error) {
                findMatches();
                startTimer();
            }
        });
    }

    void findMatches() {
        auto currentTime = std::chrono::steady_clock::now();

        for (size_t i = 0; i < queue.size(); ++i) {
            int eloDifference = 100;
            auto& player1 = queue[i];
            auto time = std::chrono::duration_cast<std::chrono::seconds>(currentTime - player1->startTime).count();

            // After 90 seconds determines the player cannot find a match in their elo range and removes them from the queue
            if (time >= 90) {
                std::cout << "Player failed to find a match" << std::endl;
                boost::asio::write(player1->socket, boost::asio::buffer("No match could be found."));
                queue.erase(queue.begin() + i);
                i--;
                continue;
            }
            // After 30 and 60 seconds increases the allowed difference in elo between the player and opponent
            else if (time >= 60) {
                eloDifference = 300;
            }
            else if (time >= 30) {
                eloDifference = 200;
            }

            // Matches 2 players together and informs them, removing them from the queue
            for (size_t j = i + 1; j < queue.size(); ++j) {
                auto& player2 = queue[j];
                if (std::abs(player1->elo - player2->elo) <= eloDifference) {
                    std::cout << "Match found between players with elo " << player1->elo << " and " << player2->elo << std::endl;

                    boost::asio::write(player1->socket, boost::asio::buffer("Match found against player with " + std::to_string(player2->elo) + " elo"));
                    boost::asio::write(player2->socket, boost::asio::buffer("Match found against player with " + std::to_string(player1->elo) + " elo"));

                    queue.erase(queue.begin() + j);
                    queue.erase(queue.begin() + i);
                    i--;
                    break;
                }
            }
        }
    }

public:
    Matchmaker(boost::asio::io_context& io_context) : timer(io_context) {
        startTimer();
    }

    void addPlayer(tcp::socket socket, int elo) {
        std::cout << "Player with " << elo << " elo has joined the matchmaking queue." << std::endl;
        queue.push_back(std::make_shared<Player>(std::move(socket), elo));
    }
};