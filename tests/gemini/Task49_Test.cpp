#include "../../source/output/gemini/cpp/Task49_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function

#include <iostream>
#include <thread>
#include <chrono>
#include <httplib.h>

int main() {
    int passed = 0, failed = 0;

    // 🟢 شغل السيرفر في Thread منفصل
    std::thread server_thread([]() {
        startUserApiServer();  // الدالة من كودك الأخير
    });

    // ⏱️ انتظر حتى يبدأ السيرفر
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "[TEST 1] test_create_user (form-urlencoded): ";
    try {
        httplib::Client cli("localhost", 8080);

        httplib::Params params{
                {"name", "John Doe"},
                {"email", "john.doe99@example.com"}
        };

        auto res = cli.Post("/users", params);

        if (res && res->status == 201 && res->body == "User created successfully") {
            std::cout << "PASSED\n";
            passed++;
        } else {
            std::cout << "FAILED (";
            if (!res) std::cout << "No response";
            else std::cout << "Status: " << res->status << ", Body: " << res->body;
            std::cout << ")\n";
            failed++;
        }
    } catch (const std::exception& e) {
        std::cout << "FAILED (Exception: " << e.what() << ")\n";
        failed++;
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));  // وقت للسيرفر

    std::cout << "\n===== Test Summary =====\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";

    exit(failed == 0 ? 0 : 1);  // ← يمنع SIGABRT

    return failed == 0 ? 0 : 1;
}
