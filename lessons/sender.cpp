#include <iostream>
#include <boost/asio.hpp>

int main() {
    try {
        std::string ip = "127.0.0.1";
        auto port = 65000u;

        boost::asio::ip::tcp::endpoint endpoint(
                boost::asio::ip::address::from_string(ip), port);
        boost::asio::io_service io_service;

        // Acceptor-а нет -- мы отправляем
        boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());
        socket.connect(endpoint);

        std::string message = "Connected!";
        std::cout << message << std::endl;

        do {
            message.push_back('\n');
            boost::asio::write(socket, boost::asio::buffer(message));
        } while (std::getline(std::cin, message));

        boost::asio::write(socket, boost::asio::buffer("EXIT\n"));

    }
    catch (std::system_error &err) {
        std::cerr << err.what();
    }
}