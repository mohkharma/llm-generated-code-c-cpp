#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "../../source/output/llama-3/cpp/Task44_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function

int testsPassed = 0;
int testsFailed = 0;

void printResult(const std::string& testName, bool passed) {
    if (passed) {
        std::cout << "[PASS] " << testName << "\n";
        testsPassed++;
    } else {
        std::cout << "[FAIL] " << testName << "\n";
        testsFailed++;
    }
}

bool simulateValidate(const std::string& input, bool shouldThrow) {
    try {
        validateInput(input);
        return !shouldThrow;
    } catch (const std::runtime_error&) {
        return shouldThrow;
    } catch (...) {
        return false;
    }
}

void test_valid_input_all_letters() {
    bool result = simulateValidate("HelloWorld", false);
    printResult("test_valid_input_all_letters", result);
}

void test_input_with_numbers() {
    bool result = simulateValidate("abc123", true);
    printResult("test_input_with_numbers", result);
}

void test_input_with_special_chars() {
    bool result = simulateValidate("hello@world!", true);
    printResult("test_input_with_special_chars", result);
}

void test_empty_input() {
    bool result = simulateValidate("", false);  // فارغ يعتبر صالح لأن لا حروف غير أبجدية فيه
    printResult("test_empty_input", result);
}

void test_input_with_space() {
    bool result = simulateValidate("hello world", true);
    printResult("test_input_with_space", result);
}

void test_input_with_uppercase() {
    bool result = simulateValidate("HELLO", false);
    printResult("test_input_with_uppercase", result);
}

void test_input_with_mixed_case() {
    bool result = simulateValidate("HelloWorld", false);
    printResult("test_input_with_mixed_case", result);
}

void test_input_with_tab() {
    bool result = simulateValidate("hello\tworld", true);
    printResult("test_input_with_tab", result);
}

void test_input_with_newline_char() {
    bool result = simulateValidate("hello\nworld", true);
    printResult("test_input_with_newline_char", result);
}

void test_long_valid_input() {
    std::string input(500, 'a');  // 500 حرف a
    bool result = simulateValidate(input, false);
    printResult("test_long_valid_input", result);
}

int main() {
    test_valid_input_all_letters();
    test_input_with_numbers();
    test_input_with_special_chars();
    test_empty_input();
    test_input_with_space();
    test_input_with_uppercase();
    test_input_with_mixed_case();
    test_input_with_tab();
    test_input_with_newline_char();
    test_long_valid_input();

    std::cout << "\nTests passed: " << testsPassed << "\n";
    std::cout << "Tests failed: " << testsFailed << "\n";
  
    return 0;
}
