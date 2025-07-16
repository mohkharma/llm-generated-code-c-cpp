#include <iostream>
#include <cstring>
#include <vector>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <algorithm>  // for std::find

#define PORT 5555
#define BUFFER_SIZE 1024

std::vector<int> clients;

void broadcast(const char* message, int sender_socket) {
    for (int client : clients) {
        if (client != sender_socket) {
            send(client, message, strlen(message), 0);
        }
    }
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) {
            std::cout << "Client disconnected or error." << std::endl;
            break;
        }
        std::cout << "Received: " << buffer << std::endl;

        broadcast(buffer, client_socket);
    }
    auto it = std::find(clients.begin(), clients.end(), client_socket);
    if (it != clients.end()) {
        clients.erase(it);
    }
    close(client_socket);
    std::cout << "Client socket closed." << std::endl;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        std::cout << "Test case result: FAIL (socket creation)" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        std::cout << "Test case result: FAIL (setsockopt)" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Prepare sockaddr_in structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        std::cout << "Test case result: FAIL (bind)" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Listen
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
        std::thread client_thread(handle_client, new_socket);
        client_thread.detach();
        std::cout << "Test case result: PASS (client connected)" << std::endl;
    }

    return 0;
}
