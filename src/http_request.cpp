#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sstream>
#include "http_request.h"

const char* server = "0.0.0.0";
const int port = 18080;

int createRequest(const std::string& endpoint) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Error: Could not open socket.\n";
        return 1;
    }

    struct sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, server, &serverAddr.sin_addr) <= 0) {
        std::cerr << "Error: Invalid address or address not supported.\n";
        close(sock);
        return 1;
    }

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error: Connection Failed.\n";
        close(sock);
        return 1;
    }

    std::stringstream ss;
    ss << "GET /" << endpoint << " HTTP/1.1\r\n"
       << "Host: " << server << ":" << port << "\r\n"
       << "Connection: close\r\n\r\n";

    std::string request = ss.str();
    send(sock, request.c_str(), request.length(), 0);

    char buffer[4096];
    ssize_t bytesReceived;
    while ((bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << buffer;
    }

    close(sock);
    return 0;
}

