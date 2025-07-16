#include <iostream>
#include <string>
#include <unordered_map>
#include <thread>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

// --- بيانات المستخدمين مخزنة داخلية ---
const std::unordered_map<std::string, std::string> users = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

// --- دالة التحقق ---
bool authenticate(const std::string& username, const std::string& password) {
    auto it = users.find(username);
    return it != users.end() && it->second == password;
}

// --- جلسة اتصال لكل عميل ---
void session(tcp::socket socket) {
    try {
        boost::asio::streambuf buf;
        boost::system::error_code error;

        while (true) {
            size_t n = boost::asio::read_until(socket, buf, '\n', error);
            if (error) break;

            std::istream is(&buf);
            std::string line;
            std::getline(is, line);

            if (!line.empty() && line.back() == '\r') line.pop_back();

            const std::string prefix = "LOGIN|";
            if (line.compare(0, prefix.size(), prefix) == 0) {
                std::string rest = line.substr(prefix.size());
                size_t sep = rest.find('|');
                if (sep != std::string::npos) {
                    std::string username = rest.substr(0, sep);
                    std::string password = rest.substr(sep + 1);

                    bool auth = authenticate(username, password);
                    std::string response = auth ? "Login successful\n" : "Invalid credentials\n";
                    boost::asio::write(socket, boost::asio::buffer(response));
                } else {
                    boost::asio::write(socket, boost::asio::buffer("Invalid format\n"));
                }
            } else {
                boost::asio::write(socket, boost::asio::buffer("Unknown command\n"));
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Session error: " << e.what() << "\n";
    }
}

// --- وظيفة السيرفر ---
void run_server() {
    try {
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));
        std::cout << "Server started on port 12345\n";

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::thread(session, std::move(socket)).detach();
        }
    } catch (std::exception& e) {
        std::cerr << "Server error: " << e.what() << "\n";
    }
}

// --- دالة اختبار تسجيل الدخول ---
bool testLogin(const std::string& username, const std::string& password, const std::string& expected_response) {
    try {
        boost::asio::io_context io_context;
        tcp::socket socket(io_context);
        tcp::resolver resolver(io_context);
        boost::asio::connect(socket, resolver.resolve("127.0.0.1", "12345"));

        std::string message = "LOGIN|" + username + "|" + password + "\n"; // ضروري \n للنهاية
        boost::asio::write(socket, boost::asio::buffer(message));

        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\n");

        std::string resp_str{
            boost::asio::buffers_begin(response.data()),
            boost::asio::buffers_begin(response.data()) + response.size()
        };

        if (!resp_str.empty() && resp_str.back() == '\n') resp_str.pop_back();

        return resp_str == expected_response;
    } catch (std::exception& e) {
        std::cerr << "Exception in testLogin: " << e.what() << "\n";
        return false;
    }
}

int main() {
    // تشغيل السيرفر في ثريد منفصل
    std::thread serverThread(run_server);

    // ننتظر قليلًا حتى يبدأ السيرفر
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // تيست كيس 1: تسجيل دخول صحيح
    bool pass1 = testLogin("user1", "pass1", "Login successful");
    std::cout << "Test case 1 (valid login): " << (pass1 ? "PASS" : "FAIL") << std::endl;

    // تيست كيس 2: تسجيل دخول خاطئ
    bool pass2 = testLogin("wronguser", "wrongpass", "Invalid credentials");
    std::cout << "Test case 2 (invalid login): " << (pass2 ? "PASS" : "FAIL") << std::endl;

    // لا نوقف السيرفر هنا (ممكن تضغط Ctrl+C لإنهاء)

    serverThread.detach();
    return 0;
}
