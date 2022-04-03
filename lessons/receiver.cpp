#include <iostream>
#include <boost/asio.hpp>

#define SPECIFIC_CLIENT

bool read(boost::asio::ip::tcp::socket& socket, std::string& message)
{
    boost::asio::streambuf buffer; // Создаём буфер
    // Читаем данные из сокета в буфер
    boost::asio::read_until(socket, buffer, '\n');
    // Оборачиваем потоком
    std::istream stream(&buffer);
    // Считываем данные из потока
    std::getline(stream, message);
    return message != "EXIT";
}

int main()
{
    auto port = 65000u;//#ifdef SPECIFIC_CLIENT
//    std::string ip = "127.0.0.1";
//	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip), port);
//#else
//    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);
//#endif
    std::string ip = "127.0.0.1";
    // Готовимся просить порт у ОС
    boost::asio::ip::tcp::endpoint endpoint(
            boost::asio::ip::address::from_string(ip), port);

    // Технический класс для передачи данных
    boost::asio::io_service io_service;

    // Начинаем слушать порт
    boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());
    acceptor.bind(endpoint);
    acceptor.listen();

    // Подключаем сокет и готовы принимать сообщения
    boost::asio::ip::tcp::socket socket(io_service);
    acceptor.accept(socket);

    std::string message;

    // Пока читается -- читаем
    while (read(socket, message)) {
        std::cout << message << std::endl;
    }
}