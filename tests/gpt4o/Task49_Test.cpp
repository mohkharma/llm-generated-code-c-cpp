#include "../../source/output/gpt4o/cpp/Task49_OPENAI_gpt-4o.cpp"  // Include the header for the function

#include <cpprest/http_client.h>
#include <thread>
#include <chrono>
#include <iostream>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::experimental::listener;

// 🟢 شغل السيرفر في thread منفصل
void run_server() {
    http_listener listener(U("http://127.0.0.1:8080/api/users"));
    listener.support(methods::POST, handle_post);

    try {
        listener.open().wait();
        std::this_thread::sleep_for(std::chrono::seconds(10));  // خليه شغال 10 ثوانٍ فقط
        listener.close().wait();
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
}

int main() {
    int passed = 0, failed = 0;

    std::thread server_thread(run_server);

    std::this_thread::sleep_for(std::chrono::seconds(1));  // انتظر بدء السيرفر

    std::wcout << L"[TEST 1] test_create_user: ";
    try {
        http_client client(U("http://127.0.0.1:8080/api/users"));

        json::value data;
        data[U("name")] = json::value::string(U("John GPT"));
        data[U("email")] = json::value::string(U("gpt@example.com"));

        auto response = client.request(methods::POST, U(""), data).get();

        if (response.status_code() == status_codes::OK) {
            auto res_json = response.extract_json().get();
            if (res_json.is_string() && res_json.as_string() == U("User added successfully!")) {
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

    server_thread.join();

    std::cout << "\n===== Test Summary =====\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
