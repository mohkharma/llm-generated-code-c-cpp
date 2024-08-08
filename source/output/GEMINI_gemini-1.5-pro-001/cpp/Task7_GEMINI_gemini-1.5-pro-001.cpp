#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fstream>
#include <sstream>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024

// Simple user struct (replace with a proper user class)
struct User {
    std::string username;
    std::string password;
};

// Function to load users from a file
std::vector<User> loadUsersFromFile(const std::string& filename) {
    std::vector<User> users;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string username, password;
            if (std::getline(iss, username, ':') && std::getline(iss, password)) {
                users.push_back({username, password});
            }
        }
        file.close();
    }
    return users;
}

// Function to check user credentials
bool authenticateUser(const std::string& username, const std::string& password, const std::vector<User>& users) {
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}

// Client function
void client() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(1);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }

    // Send login request
    std::string request = "LOGIN:" + username + ":" + password;
    send(sockfd, request.c_str(), request.length(), 0);

    // Receive response
    char buffer[MAX_BUFFER_SIZE];
    int bytes_received = recv(sockfd, buffer, MAX_BUFFER_SIZE, 0);
    if (bytes_received <= 0) {
        perror("Error receiving response");
        exit(1);
    }

    std::string response(buffer, bytes_received);
    std::cout << "Server response: " << response << std::endl;

    close(sockfd);
}

// Server function
void server() {
    int sockfd, newsockfd, pid;
    struct sockaddr_in server_addr, client_addr;
    socklen_t clilen;

    // Load users from file
    std::vector<User> users = loadUsersFromFile("users.txt");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    listen(sockfd, 5);

    clilen = sizeof(client_addr);

    while (true) {
        newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &clilen);
        if (newsockfd < 0) {
            perror("Error accepting connection");
            continue;
        }

        pid = fork();
        if (pid < 0) {
            perror("Error forking");
            exit(1);
        }
        if (pid == 0) { // child process
            close(sockfd);
            // Handle client request
            char buffer[MAX_BUFFER_SIZE];
            int bytes_received = recv(newsockfd, buffer, MAX_BUFFER_SIZE, 0);
            if (bytes_received <= 0) {
                perror("Error receiving request");
                exit(1);
            }

            std::string request(buffer, bytes_received);
            std::istringstream iss(request);
            std::string command;
            std::getline(iss, command, ':');

            if (command == "LOGIN") {
                std::string username, password;
                std::getline(iss, username, ':');
                std::getline(iss, password);

                bool authenticated = authenticateUser(username, password, users);
                std::string response = authenticated ? "LOGIN_SUCCESS" : "LOGIN_FAIL";
                send(newsockfd, response.c_str(), response.length(), 0);
            } else {
                // Handle other commands (e.g., chat messages)
                std::cout << "Unknown command: " << command << std::endl;
            }

            close(newsockfd);
            exit(0);
        } else { // parent process
            close(newsockfd);
        }
    }

    close(sockfd);
}

int main() {
    // Choose client or server mode
    int mode;
    std::cout << "Enter mode (1 for client, 2 for server): ";
    std::cin >> mode;

    if (mode == 1) {
        client();
    } else if (mode == 2) {
        server();
    } else {
        std::cout << "Invalid mode" << std::endl;
    }

    return 0;
}
// ```
//
// **Explanation:**
//
// - Includes necessary headers for network programming, file I/O, and string manipulation.
// - Defines a `User` struct to store username and password.
// - Defines `loadUsersFromFile` function to load users from a file.
// - Defines `authenticateUser` function to check user credentials.
// - Implements the `client` function to handle client-side logic.
// - Implements the `server` function to handle server-side logic, including user authentication and message handling.
// - The `main` function allows the user to choose between client and server mode.
//
// **Note:**
//
// - This code is a basic example and lacks proper error handling, security, and advanced features.
// - For production use, consider using established libraries and security protocols.
// - The `users.txt` file should contain user information in the format `username:password`.
// - This implementation only handles login requests. You can extend it to handle chat messages, user management, and other features.
