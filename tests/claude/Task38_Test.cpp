#include "../../source/output/claude/cpp/Task38_CLAUDE_claude-3-5-sonnet-20240620.cpp"
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <curl/curl.h>

int tests_passed = 0;
int tests_failed = 0;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void test_1_form_display() {
    std::cout << "[RUNNING] test_1_form_display\n";
    CURL* curl = curl_easy_init();
    std::string readBuffer;

    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res == CURLE_OK && readBuffer.find("<form method='post'>") != std::string::npos) {
        std::cout << "[PASS] test_1_form_display\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] test_1_form_display\n";
        tests_failed++;
    }
}

void test_2_post_name() {
    std::cout << "[RUNNING] test_2_post_name\n";
    CURL* curl = curl_easy_init();
    std::string readBuffer;

    // نضع name=Ahmad في query string لأن الكود الأصلي يقرأه من url_params
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/?name=Ahmad");
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");  // body فارغ
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res == CURLE_OK && readBuffer.find("Hello, Ahmad!") != std::string::npos) {
        std::cout << "[PASS] test_2_post_name\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] test_2_post_name\n";
        tests_failed++;
    }
}

int main() {
    std::thread serverThread([](){
        runCrowApp();
    });

    std::this_thread::sleep_for(std::chrono::seconds(2));

    test_1_form_display();
    test_2_post_name();

    std::cout << "\nTests passed: " << tests_passed << "\n";
    std::cout << "Tests failed: " << tests_failed << "\n";

    std::exit(0);
}
