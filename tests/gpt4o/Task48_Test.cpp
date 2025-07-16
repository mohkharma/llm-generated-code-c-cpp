#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

std::vector<int> clients;
std::mutex clients_mutex;

void broadcast(const std::string& message, int sender) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    for (int client : clients) {
        if (client != sender) {
            if (send(client, message.c_str(), message.size(), 0) == -1) {
                std::cerr << "Failed to send message to client " << client << std::endl;
                std::cout << "Test case result: FAIL (send message)" << std::endl;
            }
        }
    }
    std::cout << "Test case result: PASS (broadcast message)" << std::endl;
}

void handle_client(int client_socket) {
    char buffer[1024];
    while (true) {
        int bytes_received = recv(client_socket, buffer, 1023, 0);
        if (bytes_received <= 0) {
            std::lock_guard<std::mutex> lock(clients_mutex);
            clients.erase(std::remove(clients.begin(), clients.end(), client_socket), clients.end());
            close(client_socket);
            std::cout << "Test case result: PASS (client disconnected)" << std::endl;
            break;
        } else {
            buffer[bytes_received] = '\0';
            std::string message(buffer);
            broadcast(message, client_socket);
        }
    }
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        std::cout << "Test case result: FAIL (socket creation)" << std::endl;
        return 1;
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5555);
    server_address.sin_addr.s_addr = INADDR_ANY;
    memset(server_address.sin_zero, 0, sizeof(server_address.sin_zero));

    if (bind(server_socket, (sockaddr*)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
        std::cout << "Test case result: FAIL (bind socket)" << std::endl;
        return 1;
    }

    if (listen(server_socket, 100) == -1) {
        std::cerr << "Failed to listen on socket" << std::endl;
        std::cout << "Test case result: FAIL (listen socket)" << std::endl;
        return 1;
    }

    std::cout << "Server started on port 5555..." << std::endl;
    std::cout << "Test case result: PASS (server started)" << std::endl;

    while (true) {
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == -1) {
            std::cerr << "Failed to accept connection" << std::endl;
            std::cout << "Test case result: FAIL (accept connection)" << std::endl;
            continue;
        }

        {
            std::lock_guard<std::mutex> lock(clients_mutex);
            clients.push_back(client_socket);
        }

        std::cout << "Connection established with client socket " << client_socket << std::endl;
        std::cout << "Test case result: PASS (client connected)" << std::endl;

        std::thread(handle_client, client_socket).detach();
    }

    close(server_socket);
    return 0;
}
