#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024

std::mutex clients_mutex;
std::unordered_map<int, std::string> clients;

void handle_client(int client_socket) {
    char buffer[MAX_BUFFER_SIZE];
    std::string username;

    // Receive username
    if (recv(client_socket, buffer, MAX_BUFFER_SIZE, 0) <= 0) {
        std::cerr << "Error receiving username" << std::endl;
        close(client_socket);
        return;
    }
    username = buffer;

    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        clients[client_socket] = username;
    }

    std::cout << username << " joined the chat" << std::endl;

    while (true) {
        if (recv(client_socket, buffer, MAX_BUFFER_SIZE, 0) <= 0) {
            break;
        }

        std::string message = username + ": " + buffer;

        {
            std::lock_guard<std::mutex> lock(clients_mutex);
            for (auto& client : clients) {
                if (client.first != client_socket) {
                    send(client.first, message.c_str(), message.length(), 0);
                }
            }
        }
    }

    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        clients.erase(client_socket);
    }

    std::cout << username << " left the chat" << std::endl;
    close(client_socket);
}

int main() {
    int server_socket, new_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t clilen;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }

    listen(server_socket, 5);
    clilen = sizeof(client_addr);

    while (true) {
        new_socket = accept(server_socket, (struct sockaddr*)&client_addr, &clilen);
        if (new_socket < 0) {
            std::cerr << "Error accepting connection" << std::endl;
            continue;
        }

        std::thread t(handle_client, new_socket);
        t.detach();
    }

    close(server_socket);
    return 0;
}
