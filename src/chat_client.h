#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;
using json = nlohmann::json;

using Message = std::string;
using namespace std;

class ChatClient
{
public:
    boost::asio::io_context io_context;
    tcp::resolver resolver;
    tcp::socket socket;

    json details;

    ChatClient() : resolver(io_context), socket(io_context) {}

    // Establish a connection to the server
    void connect(const std::string &server, const std::string &port)
    {

        // Resolve the server address and port, then connect the socket
        auto endpoints = resolver.resolve(server, port);
        boost::asio::connect(socket, endpoints);
    }

    // Function to send a message to the connected server

    void sendMessage(const std::string &message)
    {

        std::string request =
            "POST /message HTTP/1.1\r\n"
            "Host: localhost\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " +
            std::to_string(message.length()) + "\r\n"
                                               "\r\n" +
            message + "\r\n";

        // Write a message to server
        boost::asio::write(socket, boost::asio::buffer(request));
    }
};