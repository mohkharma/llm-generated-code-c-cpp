#include "../../source/output/codestral/cpp/Task38_MISTRAL_codestral-latest.cpp"  // Include the header for the function
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

int tests_passed = 0;
int tests_failed = 0;

// نحاكي بيئة CGI من خلال تعيين المتغيرات البيئية قبل استدعاء الدالة
void simulate_env_and_run(const std::string& query_string, std::stringstream& output) {
    setenv("QUERY_STRING", query_string.c_str(), 1);

    // Redirect cout temporarily
    std::streambuf* original_buf = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    // استدعاء الـ main مباشرة (لأن الحل كله فيه)
    handleCGIUserInput();

    // استعادة المخرج الأصلي
    std::cout.rdbuf(original_buf);
}

void test_1_valid_input() {
    std::cout << "[RUNNING] test_1_valid_input\n";
    std::stringstream output;
    simulate_env_and_run("user_input=helloWorld", output);
    std::string result = output.str();

    if (result.find("Your input: helloWorld") != std::string::npos) {
        std::cout << "[PASS] test_1_valid_input\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] test_1_valid_input\n";
        tests_failed++;
    }
}

void test_2_missing_param() {
    std::cout << "[RUNNING] test_2_missing_param\n";
    std::stringstream output;
    simulate_env_and_run("other_param=xyz", output);
    std::string result = output.str();

    if (result.empty()) {
        std::cout << "[PASS] test_2_missing_param (no output as expected)\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] test_2_missing_param (unexpected output)\n";
        tests_failed++;
    }
}

void test_3_empty_query() {
    std::cout << "[RUNNING] test_3_empty_query\n";
    std::stringstream output;
    simulate_env_and_run("", output);
    std::string result = output.str();

    if (result.empty()) {
        std::cout << "[PASS] test_3_empty_query\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] test_3_empty_query\n";
        tests_failed++;
    }
}

int main() {
    test_1_valid_input();
    test_2_missing_param();
    test_3_empty_query();

    std::cout << "\nTests passed: " << tests_passed << "\n";
    std::cout << "Tests failed: " << tests_failed << "\n";
    return 0;
}
