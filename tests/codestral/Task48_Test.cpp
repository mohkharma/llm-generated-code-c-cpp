#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345
#define BUFFER_SIZE 1024

void broadcast(const std::vector<int>& clients, int sender_fd, char* message, ssize_t length) {
    for (int client_fd : clients) {
        if (client_fd != sender_fd) {
            send(client_fd, message, length, 0);
        }
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    std::vector<int> clients;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        std::cout << "Test case result: FAIL (socket creation)" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        std::cout << "Test case result: FAIL (setsockopt)" << std::endl;
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        std::cout << "Test case result: FAIL (bind)" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        std::cout << "Test case result: FAIL (listen)" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << PORT << std::endl;
    std::cout << "Test case result: PASS (server started)" << std::endl;

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
            perror("accept");
            std::cout << "Test case result: FAIL (accept)" << std::endl;
            continue;
        }

        clients.push_back(new_socket);
        std::cout << "Test case result: PASS (client connected)" << std::endl;

        std::thread([&, new_socket]() {
            while (true) {
                ssize_t valread = read(new_socket, buffer, BUFFER_SIZE);
                if (valread <= 0) {
                    std::cout << "Client disconnected or read error." << std::endl;
                    break;
                }
                broadcast(clients, new_socket, buffer, valread);
            }

            // Remove client socket on disconnect
            auto it = std::find(clients.begin(), clients.end(), new_socket);
            if (it != clients.end()) {
                clients.erase(it);
            }
            close(new_socket);
            std::cout << "Client socket closed." << std::endl;
        }).detach();
    }

    return 0;
}
