#include "../../source/output/codestral/cpp/Task45_MISTRAL_codestral-latest.cpp"  // Include the header for the function
#include <iostream>
#include <sstream>
#include <string>

int testsPassed = 0;
int testsFailed = 0;

void printResult(const std::string& testName, bool passed) {
    if (passed) {
        std::cout << "[PASS] " << testName << "\n";
        ++testsPassed;
    } else {
        std::cout << "[FAIL] " << testName << "\n";
        ++testsFailed;
    }
}

void simulateDoubleNumberInput(const std::string& inputStr, std::string& outputStr) {
    std::stringstream input(inputStr);
    std::stringstream output;

    std::streambuf* oldCin = std::cin.rdbuf();
    std::streambuf* oldCout = std::cout.rdbuf();

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    doubleNumberInput();  // Function under test

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    outputStr = output.str();
}

// === Test cases ===

void test_valid_input() {
    std::string output;
    simulateDoubleNumberInput("3\n", output);
    bool pass = output.find("The result is: 6") != std::string::npos;
    printResult("test_valid_input", pass);
}

void test_invalid_input() {
    std::string output;
    simulateDoubleNumberInput("abc\n", output);
    bool pass = output.find("Invalid input") != std::string::npos;
    printResult("test_invalid_input", pass);
}

void test_zero_input() {
    std::string output;
    simulateDoubleNumberInput("0\n", output);
    bool pass = output.find("The result is: 0") != std::string::npos;
    printResult("test_zero_input", pass);
}

void test_negative_input() {
    std::string output;
    simulateDoubleNumberInput("-2\n", output);
    bool pass = output.find("The result is: -4") != std::string::npos;
    printResult("test_negative_input", pass);
}

void test_decimal_input() {
    std::string output;
    simulateDoubleNumberInput("1.5\n", output);
    bool pass = output.find("The result is: 3") != std::string::npos;
    printResult("test_decimal_input", pass);
}

int main() {
    test_valid_input();
    test_invalid_input();
    test_zero_input();
    test_negative_input();
    test_decimal_input();

    std::cout << "\nTests passed: " << testsPassed << "\n";
    std::cout << "Tests failed: " << testsFailed << "\n";

    return testsFailed == 0 ? 0 : 1;
}
