#include "../../source/output/llama-3/cpp/Task50_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // startPocoFileUploadServer()

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <filesystem>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace fs = std::filesystem;
using tcp = net::ip::tcp;

int tests_passed = 0;
int tests_failed = 0;

void print_result(const std::string& test_name, bool passed) {
    if (passed) {
        std::cout << "[PASS] " << test_name << "\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] " << test_name << "\n";
        tests_failed++;
    }
}

void run_server() {
    startPocoFileUploadServer();  // ✅ دالة جديدة بدل app.run()
}

bool upload_file(const std::string& filename) {
    try {
        net::io_context ioc;
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);
        auto const results = resolver.resolve("127.0.0.1", "8000");
        stream.connect(results);

        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (!file) return false;
        auto size = file.tellg();
        file.seekg(0);
        std::string body(size, '\0');
        file.read(&body[0], size);

        http::request<http::string_body> req{http::verb::post, "/", 11};
        req.set(http::field::host, "127.0.0.1");
        req.set(http::field::content_type, "application/octet-stream");
        req.body() = std::move(body);
        req.prepare_payload();

        http::write(stream, req);
        beast::flat_buffer buffer;
        http::response<http::string_body> res;
        http::read(stream, buffer, res);
        stream.socket().shutdown(tcp::socket::shutdown_both);

        return res.result() == http::status::ok;
    } catch (...) {
        return false;
    }
}

int main() {
    const std::string test_name = "test_file_upload_success";
    const std::string test_file = "testFile.txt";
    const std::string uploaded_file = "uploaded_file";

    {
        std::ofstream out(test_file);
        out << "Test data from Poco client.";
    }

    std::thread server_thread(run_server);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    bool upload_success = upload_file(test_file);
    bool file_exists = fs::exists(uploaded_file);

    print_result(test_name, upload_success && file_exists);

    std::remove(test_file.c_str());
    std::remove(uploaded_file.c_str());

    std::cout << "\nTotal Passed: " << tests_passed << "\n";
    std::cout << "Total Failed: " << tests_failed << "\n";

    return 0;
}
