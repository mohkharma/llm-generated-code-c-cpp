#include "../../source/output/gpt4o/cpp/Task50_OPENAI_gpt-4o.cpp"  // startFileUploadServer()

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/filesystem.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace fs = boost::filesystem;
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
    startFileUploadServer();  // من ملف السيرفر
}

bool upload_file(const std::string& file_path) {
    try {
        net::io_context ioc;
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);
        auto const results = resolver.resolve("127.0.0.1", "8080");
        stream.connect(results);

        // اقرأ محتوى الملف
        std::ifstream file(file_path, std::ios::binary | std::ios::ate);
        if (!file) return false;
        auto size = file.tellg();
        file.seekg(0);
        std::string body(size, '\0');
        file.read(&body[0], size);

        // إنشاء الطلب
        http::request<http::string_body> req{http::verb::post, "/", 11};
        req.set(http::field::host, "127.0.0.1");
        req.set(http::field::content_type, "application/octet-stream");
        req.body() = std::move(body);
        req.prepare_payload();

        // إرسال الطلب واستلام الرد
        http::write(stream, req);
        beast::flat_buffer buffer;
        http::response<http::string_body> res;
        http::read(stream, buffer, res);

        stream.socket().shutdown(tcp::socket::shutdown_both);

        return res.result() == http::status::ok &&
               res.body().find("File successfully uploaded") != std::string::npos;
    } catch (...) {
        return false;
    }
}

int main() {
    const std::string test_name = "test_file_upload_success";
    const std::string test_file = "testFile.txt";
    const std::string uploaded_path = "uploads/uploaded_file";

    // 1. إنشاء ملف
    {
        std::ofstream out(test_file);
        out << "This is a test file from GPT-4o client.";
    }

    // 2. تشغيل السيرفر في Thread منفصل
    std::thread server_thread(run_server);
    std::this_thread::sleep_for(std::chrono::seconds(1));  // وقت للسيرفر

    // 3. إرسال الملف
    bool success = upload_file(test_file);

    // 4. تحقق من وجود الملف
    bool file_exists = fs::exists(uploaded_path);

    // 5. طباعة النتيجة
    print_result(test_name, success && file_exists);

    // 6. تنظيف
    std::remove(test_file.c_str());
    std::remove(uploaded_path.c_str());

    // 7. طباعة عدد النتائج
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "\nTotal Passed: " << tests_passed << "\n";
    std::cout << "Total Failed: " << tests_failed << "\n";

    return 0;
}
