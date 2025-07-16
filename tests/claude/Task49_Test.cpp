#include "../../source/output/claude/cpp/Task49_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // يحتوي على كود السيرفر

#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/http_listener.h>
#include <thread>
#include <chrono>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
using namespace web::http::client;

// دالة لتشغيل السيرفر في thread منفصل
void run_server() {
    UserHandler handler;
    http_listener listener(U("http://127.0.0.1:8080/api/users"));
    listener.support(methods::POST, std::bind(&UserHandler::handle_post, &handler, std::placeholders::_1));

    try {
        listener.open().wait();
        std::this_thread::sleep_for(std::chrono::seconds(10)); // خليه شغال 10 ثوانٍ، كافية للاختبار
        listener.close().wait();
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
}

int main() {
    int passed = 0, failed = 0;

    // 🟢 شغل السيرفر في Thread
    std::thread server_thread(run_server);

    std::this_thread::sleep_for(std::chrono::seconds(1));  // انتظر شوي قبل البدء بالاختبار

    std::wcout << L"[TEST 1] test_create_user: ";
    try {
        http_client client(U("http://127.0.0.1:8080/api/users"));
        json::value user_data;
        user_data[U("name")] = json::value::string(U("John Doe"));
        user_data[U("email")] = json::value::string(U("john.doe2@example.com"));

        http_response response = client.request(methods::POST, U(""), user_data).get();

        if (response.status_code() == status_codes::Created) {
            json::value result = response.extract_json().get();
            if (result.has_field(U("message")) && result[U("message")].as_string() == U("User created successfully")) {
                std::wcout << L"PASSED\n";
                passed++;
            } else {
                std::wcout << L"FAILED (Unexpected response content)\n";
                failed++;
            }
        } else {
            std::wcout << L"FAILED (Status code: " << response.status_code() << L")\n";
            failed++;
        }
    } catch (const std::exception& e) {
        std::wcout << L"FAILED (Exception: " << e.what() << L")\n";
        failed++;
    }

    server_thread.join();  // انتظر السيرفر لينهي

    std::cout << "\n===== Test Summary =====\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
