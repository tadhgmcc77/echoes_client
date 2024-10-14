#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include "chat_client.h"

// for convenience
using json = nlohmann::json;

int main()
{
    // Init JSON obj
    json userInfo;

    // init vars
    std::string name;
    std::string text;

    // Take user input
    std::cout << "Enter name: ";
    std::getline(std::cin, name); // read in user input and store to the var name

    std::cout << "Enter message: ";
    // std::cin.ignore(); // ignore any newline chars from the previous input
    std::getline(std::cin, text);

    // Parse input into JSON
    userInfo["name"] = name;
    userInfo["text"] = text;

    // creation of ChatClient class + print details
    ChatClient user;
    user.details = userInfo;

    // connect to test server
    user.connect("127.0.0.1", "18080");

    std::string message = R"({"name": ")" + name + R"(", "text": ")" + text + R"("})";

    user.sendMessage(message);

    return 0;
}