#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        std::cout << "Test case result: FAIL" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Attach socket to port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        std::cout << "Test case result: FAIL" << std::endl;
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        std::cout << "Test case result: FAIL" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        std::cout << "Test case result: FAIL" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << PORT << std::endl;
    std::cout << "Test case result: PASS" << std::endl;

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            std::cout << "Test case result: FAIL" << std::endl;
            continue;
        }

        std::cout << "Connection accepted" << std::endl;

        while (true) {
            memset(buffer, 0, BUFFER_SIZE);
            int valread = read(new_socket, buffer, BUFFER_SIZE);
            if (valread <= 0) break;

            std::cout << "Received: " << buffer << std::endl;
            send(new_socket, buffer, strlen(buffer), 0);
        }

        close(new_socket);
    }

    return 0;
}
