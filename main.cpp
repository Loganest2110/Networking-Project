// Used for testing, currently has no use

/*
#include <iostream>
#include <thread>
#include <chrono>

void server();
void client();

int main() {
    std::cout << "Starting server." << std::endl;

    std::thread server_thread([]() {
        server();
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Starting client." << std::endl;

    client();

    if (server_thread.joinable()) {
        server_thread.join();
    }

    return 0;
}
*/