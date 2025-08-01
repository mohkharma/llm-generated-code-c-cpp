#include "../../source/output/gemini/cpp/Task38_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

int tests_passed = 0;
int tests_failed = 0;

// نحاكي بيئة CGI عبر ضبط المتغير البيئي وتشغيل handleCGIForm
void simulate_env_and_run(const std::string& query_string, std::stringstream& output) {
    if (query_string.empty()) {
        unsetenv("QUERY_STRING");
    } else {
        setenv("QUERY_STRING", query_string.c_str(), 1);
    }

    std::streambuf* original_buf = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    handleCGIForm();

    std::cout.rdbuf(original_buf);
}

void test_1_display_form_when_no_input() {
    std::cout << "[RUNNING] test_1_display_form_when_no_input\n";
    std::stringstream output;
    simulate_env_and_run("", output);
    std::string result = output.str();

    if (result.find("<form method='get'") != std::string::npos &&
        result.find("Name:") != std::string::npos) {
        std::cout << "[PASS] test_1_display_form_when_no_input\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] test_1_display_form_when_no_input\n";
        tests_failed++;
    }
}

void test_2_display_name_if_provided() {
    std::cout << "[RUNNING] test_2_display_name_if_provided\n";
    std::stringstream output;
    simulate_env_and_run("name=Omar", output);
    std::string result = output.str();

    if (result.find("Hello, Omar!") != std::string::npos) {
        std::cout << "[PASS] test_2_display_name_if_provided\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] test_2_display_name_if_provided\n";
        tests_failed++;
    }
}

void test_3_display_invalid_if_name_missing() {
    std::cout << "[RUNNING] test_3_display_invalid_if_name_missing\n";
    std::stringstream output;
    simulate_env_and_run("age=22", output);
    std::string result = output.str();

    if (result.find("Invalid input") != std::string::npos) {
        std::cout << "[PASS] test_3_display_invalid_if_name_missing\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] test_3_display_invalid_if_name_missing\n";
        tests_failed++;
    }
}

int main() {
    test_1_display_form_when_no_input();
    test_2_display_name_if_provided();
    test_3_display_invalid_if_name_missing();

    std::cout << "\nTests passed: " << tests_passed << "\n";
    std::cout << "Tests failed: " << tests_failed << "\n";
    return 0;
}
