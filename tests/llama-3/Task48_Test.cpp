#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "Socket creation error\n";
        std::cout << "Test case result: FAIL (socket creation)\n";
        return -1;
    }
    std::cout << "Test case result: PASS (socket creation)\n";

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9090);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cout << "Invalid address/ Address not supported\n";
        std::cout << "Test case result: FAIL (address conversion)\n";
        return -1;
    }
    std::cout << "Test case result: PASS (address conversion)\n";

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "Connection Failed\n";
        std::cout << "Test case result: FAIL (connect to server)\n";
        return -1;
    }
    std::cout << "Test case result: PASS (connect to server)\n";

    std::string input;
    while (true) {
        std::getline(std::cin, input);
        if (input.empty()) continue;

        ssize_t sent_bytes = send(sock, input.c_str(), input.length(), 0);
        if (sent_bytes == -1) {
            std::cout << "Failed to send message\n";
            std::cout << "Test case result: FAIL (send message)\n";
            break;
        } else {
            std::cout << "Test case result: PASS (send message)\n";
        }
    }

    close(sock);
    return 0;
}
