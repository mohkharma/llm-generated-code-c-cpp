 #include "../../source/output/llama-3/cpp/Task45_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function
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

void simulateRunSafeCalculator(const std::string& inputStr, std::string& outputStr) {
    std::stringstream input(inputStr);
    std::stringstream output;

    std::streambuf* oldCin = std::cin.rdbuf();
    std::streambuf* oldCout = std::cout.rdbuf();

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    runSafeCalculator();

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    outputStr = output.str();
}

// === اختبارات ===

void test_valid_addition() {
    std::string output;
    simulateRunSafeCalculator("3\n4\n+\n", output);
    bool pass = output.find("Result: 7") != std::string::npos;
    printResult("test_valid_addition", pass);
}

void test_valid_division() {
    std::string output;
    simulateRunSafeCalculator("8\n2\n/\n", output);
    bool pass = output.find("Result: 4") != std::string::npos;
    printResult("test_valid_division", pass);
}

void test_divide_by_zero() {
    std::string output;
    simulateRunSafeCalculator("5\n0\n/\n", output);
    bool pass = output.find("Error: Division by zero!") != std::string::npos;
    printResult("test_divide_by_zero", pass);
}

void test_invalid_operation_char() {
    std::string output;
    simulateRunSafeCalculator("2\n3\nx\n", output);
    bool pass = output.find("Error: Invalid operation!") != std::string::npos;
    printResult("test_invalid_operation_char", pass);
}

void test_invalid_number_then_valid() {
    std::string output;
    simulateRunSafeCalculator("abc\n5\n4\n+\n", output);
    bool pass = output.find("Error: Invalid input!") != std::string::npos &&
                output.find("Result: 9") != std::string::npos;
    printResult("test_invalid_number_then_valid", pass);
}

void test_invalid_operation_input() {
    std::string output;
    simulateRunSafeCalculator("1\n2\n@\n", output);
    bool pass = output.find("Error: Invalid operation!") != std::string::npos;
    printResult("test_invalid_operation_input", pass);
}

int main() {
    test_valid_addition();
    test_valid_division();
    test_divide_by_zero();
    test_invalid_operation_char();
    test_invalid_number_then_valid();
    test_invalid_operation_input();

    std::cout << "\nTests passed: " << testsPassed << "\n";
    std::cout << "Tests failed: " << testsFailed << "\n";

    return testsFailed == 0 ? 0 : 1;
}
