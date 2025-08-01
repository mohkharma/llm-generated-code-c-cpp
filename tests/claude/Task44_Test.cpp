#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include "../../source/output/claude/cpp/Task44_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function

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

void test_valid_input() {
    bool result =
        validateInput("Hello World") &&
        validateInput("12345") &&
        validateInput("A1 B2 C3");

    printResult("test_valid_input", result);
}

void test_invalid_input_special_characters() {
    bool result =
        !validateInput("Hello@World") &&
        !validateInput("12345!") &&
        !validateInput("A1 B2 C3?");

    printResult("test_invalid_input_special_characters", result);
}

void test_empty_input() {
    bool result =
        validateInput("") &&
        processInput("") == "";

    printResult("test_empty_input", result);
}

void test_input_with_leading_and_trailing_spaces() {
    std::string input = "  Hello World  ";
    bool result =
        validateInput(input) &&
        processInput(input) == "  HELLO WORLD  ";

    printResult("test_input_with_leading_and_trailing_spaces", result);
}

void test_numeric_input() {
    std::string input = "12345";
    bool result =
        validateInput(input) &&
        processInput(input) == "12345";

    printResult("test_numeric_input", result);
}

void test_mixed_input() {
    std::string input = "abc 123";
    bool result =
        validateInput(input) &&
        processInput(input) == "ABC 123";

    printResult("test_mixed_input", result);
}

void test_invalid_input_with_newlines() {
    bool result =
        !validateInput("Hello\nWorld") &&
        !validateInput("123\n456");

    printResult("test_invalid_input_with_newlines", result);
}

void test_input_with_tabs() {
    bool result =
        !validateInput("Hello\tWorld") &&
        !validateInput("123\t456");

    printResult("test_input_with_tabs", result);
}

void test_all_valid_characters() {
    std::string input = "Valid input 123";
    bool result =
        validateInput(input) &&
        processInput(input) == "VALID INPUT 123";

    printResult("test_all_valid_characters", result);
}

void test_long_input() {
    std::string input(1000, 'a');
    bool result =
        validateInput(input) &&
        processInput(input) == std::string(1000, 'A');

    printResult("test_long_input", result);
}

int main() {
    test_valid_input();
    test_invalid_input_special_characters();
    test_empty_input();
    test_input_with_leading_and_trailing_spaces();
    test_numeric_input();
    test_mixed_input();
    test_invalid_input_with_newlines();
    test_input_with_tabs();
    test_all_valid_characters();
    test_long_input();

    std::cout << "\nTests passed: " << testsPassed << "\n";
    std::cout << "Tests failed: " << testsFailed << "\n";

    return 0;
}
