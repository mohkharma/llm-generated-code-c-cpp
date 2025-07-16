 #include "../../source/output/codestral/cpp/Task49_MISTRAL_codestral-latest.cpp"  // Include the header for the function

#include <iostream>
#include <thread>
#include <chrono>
#include <httplib.h>
#include <nlohmann/json.hpp>

int main() {
    int passed = 0, failed = 0;
    // 🟢 شغّل السيرفر في Thread منفصل
    std::thread server_thread([]() {
        startHttpUserServer();  // الدالة موجودة في ملف الحل
    });

    // ⏱️ انتظر قليلاً لإتاحة وقت للسيرفر ليبدأ
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "[TEST 1] test_create_user: ";
    try {
        httplib::Client cli("localhost", 8080);

        nlohmann::json data;
        data["name"] = "John Doe";
        data["email"] = "john.doe2@example.com";

        auto res = cli.Post("/user", data.dump(), "application/json");

        if (res && res->status == 200 && res->body == "User added successfully") {
            std::cout << "PASSED\n";
            passed++;
        } else {
            std::cout << "FAILED (";
            if (!res) {
                std::cout << "No response";
            } else {
                std::cout << "Status: " << res->status << ", Body: " << res->body;
            }
            std::cout << ")\n";
            failed++;
        }
    } catch (const std::exception& e) {
        std::cout << "FAILED (Exception: " << e.what() << ")\n";
        failed++;
    }

    // ❌ لا يمكن إيقاف httplib::Server برمجياً، لذا ننهي البرنامج هنا فقط بعد التأخير
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "\n===== Test Summary =====\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
