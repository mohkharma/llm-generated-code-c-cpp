#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

#define PORT 12345

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        std::cout << "Test case result: FAIL" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        std::cout << "socket created: PASS" << std::endl;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        std::cout << "Test case result: FAIL" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        std::cout << "setsockopt: PASS" << std::endl;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        std::cout << "Test case result: FAIL" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        std::cout << "bind: PASS" << std::endl;
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        std::cout << "Test case result: FAIL" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        std::cout << "listen: PASS" << std::endl;
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        std::cout << "Test case result: FAIL" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        std::cout << "accept: PASS" << std::endl;
    }

    while ((valread = read(new_socket, buffer, 1024)) > 0) {
        send(new_socket, buffer, valread, 0);
    }

    close(new_socket);
    close(server_fd);
    std::cout << "Test case result: PASS" << std::endl;

    return 0;
}
