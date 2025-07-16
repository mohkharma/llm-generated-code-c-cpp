#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <fstream>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <chrono>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Server {
private:
    int serverSocket;
    std::vector<int> clients;

    json authenticate(const std::string& username, const std::string& password) {
        std::ifstream file("users.txt");
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string storedUsername, storedPassword;
            if (std::getline(iss, storedUsername, ':') && std::getline(iss, storedPassword)) {
                if (username == storedUsername && password == storedPassword) {
                    return {{"status", "success"}, {"message", "Login successful"}};
                }
            }
        }
        return {{"status", "failure"}, {"message", "Invalid credentials"}};
    }

    void handleClient(int clientSocket) {
        char buffer[1024] = {0};
        while (true) {
            memset(buffer, 0, sizeof(buffer));
            int valread = read(clientSocket, buffer, 1024);
            if (valread <= 0) break;

            try {
                json request = json::parse(buffer);
                if (request["action"] == "login") {
                    json response = authenticate(request["username"], request["password"]);
                    std::string responseStr = response.dump();
                    send(clientSocket, responseStr.c_str(), responseStr.length(), 0);
                }
            } catch (...) {
                break;
            }
        }
        close(clientSocket);
    }

public:
    Server(int port) {
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        bind(serverSocket, (struct sockaddr *)&address, sizeof(address));
        listen(serverSocket, 3);
    }

    void start() {
        std::cout << "Server listening on port 5000" << std::endl;
        while (true) {
            sockaddr_in clientAddr;
            socklen_t clientAddrLen = sizeof(clientAddr);
            int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
            clients.push_back(clientSocket);
            std::thread(&Server::handleClient, this, clientSocket).detach();
        }
    }
};

class Client {
public:
    int clientSocket;

    void connectToServer(const std::string& ip, int port) {
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);

        ::connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    }

    void login(const std::string& username, const std::string& password) {
        json request = {
            {"action", "login"},
            {"username", username},
            {"password", password}
        };

        std::string requestStr = request.dump();
        send(clientSocket, requestStr.c_str(), requestStr.length(), 0);

        char buffer[1024] = {0};
        read(clientSocket, buffer, 1024);
        json response = json::parse(buffer);
        std::cout << response["message"] << std::endl;
    }

    void disconnect() {
        close(clientSocket);
    }
};

// --- Functions for testing ---

void createUsersFile() {
    std::ofstream ofs("users.txt");
    ofs << "user1:pass1\n";
    ofs << "user2:pass2\n";
    ofs.close();
}

bool testLoginValidUser() {
    Client client;
    client.connectToServer("127.0.0.1", 5000);

    json request = {
        {"action", "login"},
        {"username", "user1"},
        {"password", "pass1"}
    };

    std::string requestStr = request.dump();
    send(client.clientSocket, requestStr.c_str(), requestStr.length(), 0);

    char buffer[1024] = {0};
    int read_bytes = read(client.clientSocket, buffer, 1024);
    if (read_bytes <= 0) return false;

    json response = json::parse(buffer);
    client.disconnect();

    return (response["status"] == "success" && response["message"] == "Login successful");
}

bool testLoginInvalidUser() {
    Client client;
    client.connectToServer("127.0.0.1", 5000);

    json request = {
        {"action", "login"},
        {"username", "wronguser"},
        {"password", "wrongpass"}
    };

    std::string requestStr = request.dump();
    send(client.clientSocket, requestStr.c_str(), requestStr.length(), 0);

    char buffer[1024] = {0};
    int read_bytes = read(client.clientSocket, buffer, 1024);
    if (read_bytes <= 0) return false;

    json response = json::parse(buffer);
    client.disconnect();

    return (response["status"] == "failure" && response["message"] == "Invalid credentials");
}

// ---- Main function runs server and tests ----

int main() {
    createUsersFile();

    std::thread serverThread([](){
        Server server(5000);
        server.start();
    });

    // انتظر حتى يعمل السيرفر قبل بدء الاختبارات
    std::this_thread::sleep_for(std::chrono::seconds(1));

    bool pass1 = testLoginValidUser();
    std::cout << "Test case 1 (valid login): " << (pass1 ? "PASS" : "FAIL") << std::endl;

    bool pass2 = testLoginInvalidUser();
    std::cout << "Test case 2 (invalid login): " << (pass2 ? "PASS" : "FAIL") << std::endl;

    // فصل الخيط حتى لا يبقى معلقاً (غير مطلوب عادة في اختبار بسيط)
    serverThread.detach();

    return 0;
}
