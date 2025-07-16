#include <iostream>
#include <sstream>
#include <string>
#include "../../source/output/gemini/cpp/Task44_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function

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

// أداة لمساعدتنا على محاكاة cin
bool test_getIntegerInput(const std::string& simulatedInput, int expectedValue) {
    std::istringstream input(simulatedInput);
    std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());

    int result = getIntegerInput("Enter an integer: ");

    std::cin.rdbuf(oldCin);  // Restore std::cin

    return result == expectedValue;
}

void test_valid_integer_input() {
    bool result = test_getIntegerInput("42\n", 42);
    printResult("test_valid_integer_input", result);
}

void test_input_with_non_integer_then_integer() {
    bool result = test_getIntegerInput("abc\n99\n", 99);
    printResult("test_input_with_non_integer_then_integer", result);
}

void test_input_with_multiple_invalids_then_valid() {
    bool result = test_getIntegerInput("x\ny\nz\n100\n", 100);
    printResult("test_input_with_multiple_invalids_then_valid", result);
}

void test_negative_integer_input() {
    bool result = test_getIntegerInput("-123\n", -123);
    printResult("test_negative_integer_input", result);
}

void test_zero_input() {
    bool result = test_getIntegerInput("0\n", 0);
    printResult("test_zero_input", result);
}

int main() {
    test_valid_integer_input();
    test_input_with_non_integer_then_integer();
    test_input_with_multiple_invalids_then_valid();
    test_negative_integer_input();
    test_zero_input();

    std::cout << "\nTests passed: " << testsPassed << "\n";
    std::cout << "Tests failed: " << testsFailed << "\n";

    return 0;
}
