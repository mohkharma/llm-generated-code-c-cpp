#include "../../source/output/gemini/cpp/Task45_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
#include <iostream>
#include <stdexcept>
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

// === Test cases ===

void test_addition() {
    bool pass = performOperation(1, 3, 4) == 7;
    printResult("test_addition", pass);
}

void test_subtraction() {
    bool pass = performOperation(2, 10, 6) == 4;
    printResult("test_subtraction", pass);
}

void test_multiplication() {
    bool pass = performOperation(3, 5, -2) == -10;
    printResult("test_multiplication", pass);
}

void test_division() {
    try {
        double result = performOperation(4, 8, 2);
        bool pass = result == 4.0;
        printResult("test_division", pass);
    } catch (...) {
        printResult("test_division", false);
    }
}

void test_division_by_zero() {
    try {
        performOperation(4, 5, 0);
        printResult("test_division_by_zero", false);  // يفترض أن يرمي خطأ
    } catch (const std::runtime_error& e) {
        printResult("test_division_by_zero", true);
    } catch (...) {
        printResult("test_division_by_zero", false);
    }
}

void test_invalid_choice() {
    try {
        performOperation(99, 1, 2);
        printResult("test_invalid_choice", false);  // يفترض أن يرمي invalid_argument
    } catch (const std::invalid_argument& e) {
        printResult("test_invalid_choice", true);
    } catch (...) {
        printResult("test_invalid_choice", false);
    }
}

int main() {
    test_addition();
    test_subtraction();
    test_multiplication();
    test_division();
    test_division_by_zero();
    test_invalid_choice();

    std::cout << "\nTests passed: " << testsPassed << "\n";
    std::cout << "Tests failed: " << testsFailed << "\n";

    return testsFailed == 0 ? 0 : 1;
}
