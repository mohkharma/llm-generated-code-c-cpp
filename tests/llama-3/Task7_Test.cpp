#include <iostream>
#include <string>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <chrono>

bool authenticate(const std::string& username, const std::string& password) {
    std::ifstream file("users.txt");
    std::string line;
    while (std::getline(file, line)) {
        size_t colonPos = line.find(":");
        if (colonPos != std::string::npos) {
            std::string user = line.substr(0, colonPos);
            std::string pwd = line.substr(colonPos + 1);
            if (user == username && pwd == password) {
                return true;
            }
        }
    }
    return false;
}

void server() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(10000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("bind failed");
        exit(1);
    }

    if (listen(serverSocket, 1) < 0) {
        perror("listen failed");
        exit(1);
    }

    std::cout << "Server started. Waiting for connections...\n";

    int connection = accept(serverSocket, nullptr, nullptr);
    if (connection < 0) {
        perror("accept failed");
        exit(1);
    }
    std::cout << "Connected to client\n";

    char buffer[1024];
    while (true) {
        ssize_t received_bytes = recv(connection, buffer, sizeof(buffer)-1, 0);
        if (received_bytes <= 0) {
            std::cout << "Connection closed or error\n";
            break;
        }
        buffer[received_bytes] = '\0';

        std::string data(buffer);

        if (data.find("LOGIN") == 0) {
            size_t spacePos = data.find(" ");
            if (spacePos != std::string::npos) {
                std::string username = data.substr(spacePos + 1);
                spacePos = username.find(" ");
                if (spacePos != std::string::npos) {
                    std::string password = username.substr(spacePos + 1);
                    username = username.substr(0, spacePos);
                    // Remove trailing newline from password if any
                    if (!password.empty() && (password.back() == '\n' || password.back() == '\r')) password.pop_back();

                    if (authenticate(username, password)) {
                        send(connection, "LOGIN_SUCCESS", 12, 0);
                    } else {
                        send(connection, "LOGIN_FAILED", 12, 0);
                    }
                } else {
                    send(connection, "LOGIN_FAILED", 12, 0);
                }
            } else {
                send(connection, "LOGIN_FAILED", 12, 0);
            }
        } else {
            std::cout << "Received message: " << data << std::endl;
            std::string response = "Server received your message: " + data;
            send(connection, response.c_str(), response.length(), 0);
        }
    }
    close(connection);
    close(serverSocket);
}

bool client_test(const std::string& username, const std::string& password, const std::string& expected_response, const std::string& test_name) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cout << test_name << ": FAIL (socket creation)\n";
        return false;
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(10000);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << test_name << ": FAIL (connect)\n";
        close(sock);
        return false;
    }

    std::string msg = "LOGIN " + username + " " + password;
    send(sock, msg.c_str(), msg.size(), 0);

    char buffer[1024]{0};
    ssize_t valread = read(sock, buffer, 1024);
    close(sock);
    if (valread <= 0) {
        std::cout << test_name << ": FAIL (read)\n";
        return false;
    }

    std::string response(buffer, valread);

    if (response == expected_response) {
        std::cout << test_name << ": PASS\n";
        return true;
    } else {
        std::cout << test_name << ": FAIL\nExpected: " << expected_response << "\nGot     : " << response << std::endl;
        return false;
    }
}

int main() {
    // تأكد من وجود ملف users.txt في نفس مجلد التنفيذ بمحتوى مثل:
    // user1:pass1
    // user2:pass2

    std::thread server_thread(server);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    client_test("user1", "pass1", "LOGIN_SUCCESS", "Test case 1 (valid login)");
    client_test("wronguser", "wrongpass", "LOGIN_FAILED", "Test case 2 (invalid login)");

    server_thread.detach();

    return 0;
}
