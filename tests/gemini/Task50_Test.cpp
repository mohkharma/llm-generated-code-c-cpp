#include "../../source/output/gemini/cpp/Task50_GEMINI_gemini-1.5-pro-001.cpp"  // سيرفر Gemini

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#define SERVER_PORT 65432
#define SERVER_ADDR "127.0.0.1"

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
    extern void start_server();  // من ملف السيرفر
    start_server();              // يستقبل طلب واحد ثم يخرج
}

bool send_file(const std::string& filename) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed\n";
        return false;
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, SERVER_ADDR, &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address\n";
        close(sock);
        return false;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed\n";
        close(sock);
        return false;
    }

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << "\n";
        close(sock);
        return false;
    }

    auto size = file.tellg();
    file.seekg(0);

    std::string filesize_str = std::to_string(size);

    // إرسال اسم الملف
    send(sock, filename.c_str(), filename.size() + 1, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // إرسال حجم الملف
    send(sock, filesize_str.c_str(), filesize_str.size() + 1, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // إرسال محتوى الملف
    char buffer[1024];
    while (!file.eof()) {
        file.read(buffer, sizeof(buffer));
        send(sock, buffer, file.gcount(), 0);
    }

    // قراءة الرد من السيرفر
    char response[1024] = {0};
    int len = recv(sock, response, sizeof(response), 0);
    close(sock);

    return std::string(response, len).find("File uploaded successfully") != std::string::npos;
}

int main() {
    const std::string test_name = "test_file_upload_success";
    const std::string test_file = "testFile.txt";
    const std::string uploaded_file = test_file;

    // 1. إنشاء ملف اختبار
    {
        std::ofstream out(test_file);
        out << "Test content from Gemini client.\n";
    }

    // 2. تشغيل السيرفر في thread منفصل
    std::thread server_thread(run_server);
    std::this_thread::sleep_for(std::chrono::seconds(1));  // إعطاء وقت للسيرفر ليشتغل

    // 3. إرسال الملف
    bool success = send_file(test_file);

    // 4. تحقق من وجود الملف على القرص
    bool file_exists = std::ifstream(uploaded_file).good();

    // 5. طباعة نتيجة الاختبار
    print_result(test_name, success && file_exists);

    // 6. تنظيف الملفات المؤقتة
    std::remove(test_file.c_str());
    std::remove(uploaded_file.c_str());

    // 7. انتظار قبل الإنهاء للسماح للطباعة بالخروج
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "\nTotal Passed: " << tests_passed << "\n";
    std::cout << "Total Failed: " << tests_failed << "\n";

    return 0;
}
