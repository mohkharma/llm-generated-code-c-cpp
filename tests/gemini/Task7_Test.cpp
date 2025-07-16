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
#include <thread>
#include <chrono>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024

struct User {
    std::string username;
    std::string password;
};

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

bool authenticateUser(const std::string& username, const std::string& password, const std::vector<User>& users) {
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}

void client_test(const std::string& username, const std::string& password, const std::string& expected_response, const std::string& test_name) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        std::cout << test_name << ": FAIL (socket error)" << std::endl;
        return;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        std::cout << test_name << ": FAIL (connect error)" << std::endl;
        close(sockfd);
        return;
    }

    std::string request = "LOGIN:" + username + ":" + password;
    send(sockfd, request.c_str(), request.length(), 0);

    char buffer[MAX_BUFFER_SIZE];
    int bytes_received = recv(sockfd, buffer, MAX_BUFFER_SIZE, 0);
    if (bytes_received <= 0) {
        perror("Error receiving response");
        std::cout << test_name << ": FAIL (recv error)" << std::endl;
        close(sockfd);
        return;
    }

    std::string response(buffer, bytes_received);

    // Remove trailing newline or spaces
    response.erase(response.find_last_not_of(" \n\r\t")+1);

    if (response == expected_response) {
        std::cout << test_name << ": PASS" << std::endl;
    } else {
        std::cout << test_name << ": FAIL" << std::endl;
        std::cout << "  Expected: " << expected_response << std::endl;
        std::cout << "  Got     : " << response << std::endl;
    }

    close(sockfd);
}

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

void server() {
    int sockfd, newsockfd, pid;
    struct sockaddr_in server_addr, client_addr;
    socklen_t clilen;

    std::vector<User> users = loadUsersFromFile("users.txt");
    if (users.empty()) {
        std::cerr << "Warning: users.txt empty or not found. No users loaded." << std::endl;
    }

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
            char buffer[MAX_BUFFER_SIZE];
            int bytes_received = recv(newsockfd, buffer, MAX_BUFFER_SIZE, 0);
            if (bytes_received <= 0) {
                perror("Error receiving request");
                close(newsockfd);
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
                std::cout << "Unknown command: " << command << std::endl;
            }

            close(newsockfd);
            exit(0);
        } else {
            close(newsockfd);
        }
    }

    close(sockfd);
}

int main() {
    std::cout << "Starting server in background thread...\n";
    std::thread server_thread([](){
        server();
    });

    // انتظر 2 ثانية حتى السيرفر يشتغل تمام
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // تنفيذ تيست كيسز
    client_test("user1", "pass1", "LOGIN_SUCCESS", "Test case 1 (valid login)");
    client_test("wronguser", "wrongpass", "LOGIN_FAIL", "Test case 2 (invalid login)");

    // انتظر السيرفر مفتوح (أو اغلق البرنامج ب Ctrl+C)
    server_thread.detach();

    return 0;
}
