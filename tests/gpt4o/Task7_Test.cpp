#include <iostream>
#include <string>
#include <unordered_map>
#include <thread>
#include <boost/asio.hpp>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using boost::asio::ip::tcp;

// بيانات المستخدمين
const std::unordered_map<std::string, std::string> users = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

bool authenticate(const std::string& username, const std::string& password) {
    auto it = users.find(username);
    return it != users.end() && it->second == password;
}

void session(tcp::socket socket) {
    try {
        char data[1024];
        boost::system::error_code error;
        size_t length = socket.read_some(boost::asio::buffer(data), error);
        if (error) return;

        std::string received(data, length);
        size_t sep = received.find(':');
        if (sep == std::string::npos) {
            boost::asio::write(socket, boost::asio::buffer("LOGIN_FAIL"));
            return;
        }
        std::string username = received.substr(0, sep);
        std::string password = received.substr(sep + 1);

        std::string response = authenticate(username, password) ? "LOGIN_SUCCESS" : "LOGIN_FAIL";
        boost::asio::write(socket, boost::asio::buffer(response));
    } catch (...) {}
}

void run_server() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));
        std::cout << "Server running on port 12345\n";

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::thread(session, std::move(socket)).detach();
        }
    } catch (std::exception& e) {
        std::cerr << "Server error: " << e.what() << "\n";
    }
}

bool client_test(const std::string& username, const std::string& password, const std::string& expected_response, const std::string& test_name) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cout << test_name << ": FAIL (socket creation)\n";
        return false;
    }

    struct sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << test_name << ": FAIL (connect)\n";
        close(sock);
        return false;
    }

    std::string msg = username + ":" + password;
    send(sock, msg.c_str(), msg.size(), 0);

    char buffer[1024]{0};
    ssize_t valread = read(sock, buffer, 1024);
    close(sock);
    if (valread <= 0) {
        std::cout << test_name << ": FAIL (read)\n";
        return false;
    }

    std::string response(buffer, valread);
    while (!response.empty() && (response.back() == '\n' || response.back() == '\r')) {
        response.pop_back();
    }

    if (response == expected_response) {
        std::cout << test_name << ": PASS\n";
        return true;
    } else {
        std::cout << test_name << ": FAIL\nExpected: " << expected_response << "\nGot     : " << response << "\n";
        return false;
    }
}

int main() {
    std::thread server_thread(run_server);

    // ننتظر قليلاً حتى يبدأ السيرفر
    std::this_thread::sleep_for(std::chrono::seconds(1));

    client_test("user1", "pass1", "LOGIN_SUCCESS", "Test case 1 (valid login)");
    client_test("wronguser", "wrongpass", "LOGIN_FAIL", "Test case 2 (invalid login)");

    server_thread.detach();
    return 0;
}
