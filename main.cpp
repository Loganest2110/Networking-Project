#include <iostream>
#include <boost/asio.hpp>

int main() {
    boost::asio::io_context io;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
    t.wait(); // Synchronous wait
    std::cout << "Boost.Asio is working!" << std::endl;
    return 0;
}