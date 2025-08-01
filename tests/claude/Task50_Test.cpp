#include "../../source/output/claude/cpp/Task50_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the server header

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>
#include <filesystem>

using boost::asio::ip::tcp;

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
    try {
        boost::asio::io_context io_context;
        FileUploadServer server(io_context, 5000);
        io_context.run();
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << "\n";
    }
}

bool send_file_to_server(const std::string& file_path, const std::string& filename) {
    try {
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "5000");
        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::ifstream file(file_path, std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open file: " << file_path << "\n";
            return false;
        }

        // Send filename
        boost::asio::write(socket, boost::asio::buffer(filename));

        // Wait briefly before sending file content
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Send file content
        std::vector<char> buffer(1024);
        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
            boost::asio::write(socket, boost::asio::buffer(buffer.data(), file.gcount()));
        }

        // Wait for confirmation
        std::vector<char> response_buf(1024);
        boost::system::error_code error;
        size_t len = socket.read_some(boost::asio::buffer(response_buf), error);
        std::string response(response_buf.begin(), response_buf.begin() + len);

        return response.find("File uploaded successfully") != std::string::npos;
    } catch (const std::exception& e) {
        std::cerr << "Client error: " << e.what() << "\n";
        return false;
    }
}

int main() {
    std::string test_name = "test_file_upload_success";

    // 1. إنشاء ملف لاختباره
    std::string test_file = "testFile.txt";
    std::string uploaded_path = "uploads/" + test_file;
    {
        std::ofstream out(test_file);
        out << "Sample content for upload test.";
    }

    // 2. تشغيل السيرفر في Thread منفصل
    std::thread server_thread(run_server);
    std::this_thread::sleep_for(std::chrono::seconds(1));  // انتظار بدء السيرفر

    // 3. تنفيذ الاختبار
    bool success = send_file_to_server(test_file, test_file);

    // 4. تحقق من إنشاء الملف
    bool file_exists = std::filesystem::exists(uploaded_path);

    // 5. تقييم النتيجة
    print_result(test_name, success && file_exists);

    // 6. تنظيف
    std::remove(test_file.c_str());
    std::remove(uploaded_path.c_str());

    // 7. إنهاء السيرفر بالقوة (اختياري حسب التطبيق)
    // 7. انتظار لفترة قصيرة قبل الإنهاء (للسماح للطباعة بالخروج)
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // تقرير نهائي قبل الخروج
    std::cout << "\nTotal Passed: " << tests_passed << "\n";
    std::cout << "Total Failed: " << tests_failed << "\n";

    return 0;

    // تقرير نهائي
    std::cout << "\nTotal Passed: " << tests_passed << "\n";
    std::cout << "Total Failed: " << tests_failed << "\n";

 }
