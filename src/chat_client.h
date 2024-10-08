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
    string name;
    string email;

    void getDetails()
    {
        cout << "Username: " << name << endl;
        cout << "Email: " << email << endl;
    }
};