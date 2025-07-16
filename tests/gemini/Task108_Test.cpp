#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

bool sendCommandAndCheckResponse(int sock, const std::string& cmd, const std::string& expected_response) {
    send(sock, cmd.c_str(), cmd.size(), 0);
    char buffer[1024] = {0};
    ssize_t valread = read(sock, buffer, sizeof(buffer)-1);
    if(valread <= 0) return false;
    std::string response(buffer, valread);
    return response == expected_response;
}

int main() {
    struct sockaddr_in serv_addr;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation error\n";
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported\n";
        return 1;
    }

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed\n";
        return 1;
    }

    // Your python test commands:
    struct Test {
        std::string cmd;
        std::string expected_response;
        std::string name;
    };

    Test tests[] = {
        {"get_value\n", "Command received", "test_get_initial_value"},
        {"set_value 10\n", "Command received", "test_set_value"},
        {"increment\n", "Command received", "test_increment"},
        {"increment\n", "Command received", "test_multiple_increments (1)"},
        {"increment\n", "Command received", "test_multiple_increments (2)"},
        {"increment\n", "Command received", "test_multiple_increments (3)"},
        {"increment\n", "Command received", "test_multiple_increments (4)"},
        {"increment\n", "Command received", "test_multiple_increments (5)"},
    };

    for(auto& t : tests) {
        bool pass = sendCommandAndCheckResponse(sock, t.cmd, t.expected_response);
        std::cout << t.name << ": " << (pass ? "PASS" : "FAIL") << "\n";
    }

    close(sock);
    return 0;
}
