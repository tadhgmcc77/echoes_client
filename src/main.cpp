#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // User input for username and message body
    std::string username, body;
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter message body: ";
    std::getline(std::cin, body);

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    // Define the server address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(4729); // Port number
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr); // Localhost

    // Connect to the server
    if (connect(sock, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        close(sock);
        return -1;
    }

    // Get the current timestamp
    time_t timestamp = time(nullptr);

    // Create the HTTP PUT request body
    std::string requestBody = "username=" + username + "&timestamp=" + std::to_string(timestamp) + "&body=" + body;

    // Specify the desired endpoint here
    std::string endpoint = "/putMessage"; // Change this to your desired endpoint

    // Create the HTTP request string (change "POST" to "PUT")
    std::string request = "PUT " + endpoint + " HTTP/1.1\r\n"
                          "Host: 127.0.0.1:4729\r\n"
                          "Content-Type: application/x-www-form-urlencoded\r\n"
                          "Content-Length: " + std::to_string(requestBody.size()) + "\r\n"
                          "Connection: close\r\n"
                          "\r\n" + requestBody;

    // Send the HTTP request
    send(sock, request.c_str(), request.size(), 0);

    // Read the server's response
    char response[4096]; // Buffer to store the response
    int bytesRead = recv(sock, response, sizeof(response) - 1, 0); // Receive response
    if (bytesRead > 0) {
        response[bytesRead] = '\0'; // Null-terminate the response
        std::cout << "Response from server:\n" << response << std::endl; // Print the response
    } else {
        std::cerr << "Failed to read response from server" << std::endl;
    }

    // Close the socket
    close(sock);

    return 0;
}
