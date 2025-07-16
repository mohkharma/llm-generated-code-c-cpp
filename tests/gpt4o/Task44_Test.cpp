#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include "../../source/output/gpt4o/cpp/Task44_OPENAI_gpt-4o.cpp"  // Include the header for the function

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

bool simulateInputOutput(const std::string& inputStr, const std::string& expectedOutputSubstring) {
    std::istringstream input(inputStr);
    std::ostringstream output;

    // حفظ std::cin و std::cout الأصليين
    std::streambuf* origCin = std::cin.rdbuf();
    std::streambuf* origCout = std::cout.rdbuf();

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    readAndSquareNumber();

    // استعادة std::cin و std::cout
    std::cin.rdbuf(origCin);
    std::cout.rdbuf(origCout);

    // تحقق من أن المخرجات تحتوي ما نتوقعه
    std::string actualOutput = output.str();
    return actualOutput.find(expectedOutputSubstring) != std::string::npos;
}

void test_valid_input() {
    bool result = simulateInputOutput("7\n", "Square of the number: 49");
    printResult("test_valid_input", result);
}

void test_negative_input() {
    bool result = simulateInputOutput("-4\n", "Square of the number: 16");
    printResult("test_negative_input", result);
}

void test_zero_input() {
    bool result = simulateInputOutput("0\n", "Square of the number: 0");
    printResult("test_zero_input", result);
}

void test_non_numeric_then_valid_input() {
    bool result = simulateInputOutput("hello\n8\n", "Square of the number: 64");
    printResult("test_non_numeric_then_valid_input", result);
}

void test_multiple_invalid_then_valid() {
    bool result = simulateInputOutput("abc\n!\nxyz\n5\n", "Square of the number: 25");
    printResult("test_multiple_invalid_then_valid", result);
}

int main() {
    test_valid_input();
    test_negative_input();
    test_zero_input();
    test_non_numeric_then_valid_input();
    test_multiple_invalid_then_valid();

    std::cout << "\nTests passed: " << testsPassed << "\n";
    std::cout << "Tests failed: " << testsFailed << "\n";
    return 0;
}
