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
    json details;

    void getDetails()
    {
        cout << "Username: " << details["name"] << endl;
        cout << "Email: " << details["email"] << endl;
    }
};