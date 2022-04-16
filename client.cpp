#include <iostream>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>


void reader(boost::asio::ip::tcp::socket &socket) {
    while (true) {
        boost::asio::streambuf buffer;
        boost::asio::read_until(socket, buffer, '\n');
        std::string data = boost::asio::buffer_cast<const char *>(buffer.data());
        if (data != "") {
            std::cout << data;
        }
    }
}

void sender(boost::asio::ip::tcp::socket &socket) {
    std::string message;
    while (true) {
        std::getline(std::cin, message);
        if (message != "") {
            const std::string msg = message + "\n";
            boost::asio::write(socket, boost::asio::buffer(msg));
        }
    }
}

int main() {
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);
    socket.connect(boost::asio::ip::tcp::endpoint(
            boost::asio::ip::address::from_string("127.0.0.1"),
            1234));
    std::thread thread_sender(sender, std::ref(socket));
    std::thread thread_reader(reader, std::ref(socket));
    thread_sender.join();
    thread_reader.join();
    return 0;
}