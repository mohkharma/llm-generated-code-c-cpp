// Task160_Test.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

// ----------- Simulate the HTTP request function (like foo in Python) -----------
std::string foo(const std::string& url,
                int simulated_status_code,
                const std::string& simulated_text,
                bool simulate_error = false)
{
    // في التطبيق الحقيقي هنا نستعمل curl
    // لكن في الاختبار سنحاكي الردود المختلفة

    if (simulate_error)
    {
        return "ERROR";
    }

    // حتى لو status_code مش 200 أو 302، نرجع النص مباشرة مثل الـ Python test
    return simulated_text;
}

// ----------------- Helper function to simulate test execution ------------------
void run_test_case(const std::string& test_name,
                   const std::string& url,
                   int simulated_status_code,
                   const std::string& simulated_text,
                   bool simulate_error,
                   const std::string& expected_result)
{
    std::string result = foo(url, simulated_status_code, simulated_text, simulate_error);
    if (result == expected_result)
    {
        std::cout << "[PASS] " << test_name << "\n";
    }
    else
    {
        std::cout << "[FAIL] " << test_name << "\n";
        std::cout << "  URL: " << url << "\n";
        std::cout << "  Expected: " << (expected_result.empty() ? "''(empty)" : expected_result) << "\n";
        std::cout << "  Got:      " << (result.empty() ? "''(empty)" : result) << "\n";
    }
}

// ------------------------------ Main test suite ------------------------------
int main()
{
    // 1. test_valid_url_google
    run_test_case("test_valid_url_google",
                  "https://www.google.com",
                  200,
                  "Success",
                  false,
                  "Success");

    // 2. test_valid_url_bing
    run_test_case("test_valid_url_bing",
                  "https://www.bing.com",
                  200,
                  "Success",
                  false,
                  "Success");

    // 3. test_invalid_url
    run_test_case("test_invalid_url",
                  "https://www.nonexistentwebsite.com",
                  0,
                  "",
                  true,   // simulate error
                  "ERROR");

    // 4. test_http_error
    run_test_case("test_http_error",
                  "https://www.example.com",
                  0,
                  "",
                  true,
                  "ERROR");

    // 5. test_network_error
    run_test_case("test_network_error",
                  "https://www.example.com",
                  0,
                  "",
                  true,
                  "ERROR");

    // 6. test_redirect
    run_test_case("test_redirect",
                  "https://www.example.com",
                  302,
                  "Redirected",
                  false,
                  "Redirected");

    // 7. test_large_response
    std::string large_text(10000, 'A');
    run_test_case("test_large_response",
                  "https://www.example.com",
                  200,
                  large_text,
                  false,
                  large_text);

    // 8. test_timeout
    run_test_case("test_timeout",
                  "https://www.example.com",
                  0,
                  "",
                  true,
                  "ERROR");

    // 9. test_no_response
    run_test_case("test_no_response",
                  "https://www.example.com",
                  200,
                  "",   // None text in Python => empty string here
                  false,
                  "");

    // 10. test_partial_content
    run_test_case("test_partial_content",
                  "https://www.example.com",
                  206,
                  "Partial content",
                  false,
                  "Partial content");

    return 0;
}
