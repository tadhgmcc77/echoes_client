#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

std::string createJsonPayload(const std::string& username, int timestamp, const std::string& body) {
    return "{ \"username\": \"" + username + "\", \"timestamp\": " + std::to_string(timestamp) + ", \"body\": \"" + body + "\" }";
}

void sendPostRequest(const std::string& jsonPayload) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Error creating socket." << std::endl;
        return;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(80); // Change to 443 for HTTPS

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "YOUR_SERVER_IP", &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid address." << std::endl;
        return;
    }

    if (connect(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Connection failed." << std::endl;
        return;
    }

    std::string httpRequest = "POST /your/api/endpoint HTTP/1.1\r\n"
                               "Host: YOUR_SERVER_IP\r\n"
                               "Content-Type: application/json\r\n"
                               "Content-Length: " + std::to_string(jsonPayload.length()) + "\r\n"
                               "Connection: close\r\n"
                               "\r\n" +
                               jsonPayload;

    send(sock, httpRequest.c_str(), httpRequest.length(), 0);
    
    char buffer[1024] = {0};
    int bytesReceived = read(sock, buffer, 1024);
    if (bytesReceived > 0) {
        std::cout << "Response: " << std::string(buffer, bytesReceived) << std::endl;
    }

    close(sock);
}

int main() {
    std::string username = "Alice";
    int timestamp = 1630000000; // Example timestamp
    std::string messageBody = "Hello, world!";
    
    std::string jsonPayload = createJsonPayload(username, timestamp, messageBody);
    sendPostRequest(jsonPayload);

    return 0;
}
