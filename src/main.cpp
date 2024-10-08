#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

// for convenience
using json = nlohmann::json;

int main()
{
    // Init JSON obj
    json userInfo;

    // init vars
    std::string name;
    std::string email;

    // Take user input
    std::cout << "Enter name: ";
    std::getline(std::cin, name); // read in user input and store to the var name

    std::cout << "Enter  email: ";
    // std::cin.ignore(); // ignore any newline chars from the previous input
    std::getline(std::cin, email);

    // Parse input into JSON
    userInfo["name"] = name;
    userInfo["email"] = email;

    // Print the JSON
    std::cout << "JSON: \n";
    std::cout << userInfo.dump(4) << std::endl;

    return 0;
}