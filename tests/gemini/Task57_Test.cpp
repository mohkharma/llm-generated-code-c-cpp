#include "../../source/output/gemini/cpp/Task57_GEMINI_gemini-1.5-pro-001.cpp"

#include <iostream>
#include <sstream>

int tests_run = 0;
int tests_passed = 0;

#define ASSERT_EQ(actual, expected) \
    do { \
        ++tests_run; \
        if ((actual) == (expected)) { \
            std::cout << "[PASS] " << __func__ << "\n"; \
            ++tests_passed; \
        } else { \
            std::cout << "[FAIL] " << __func__ << ": Expected " << expected << " but got " << actual << "\n"; \
        } \
    } while (0)

#define ASSERT_TRUE(condition) \
    do { \
        ++tests_run; \
        if ((condition)) { \
            std::cout << "[PASS] " << __func__ << "\n"; \
            ++tests_passed; \
        } else { \
            std::cout << "[FAIL] " << __func__ << "\n"; \
        } \
    } while (0)

void test_factorial_zero() {
    ASSERT_EQ(computeFactorial(0), 1);
}

void test_factorial_one() {
    ASSERT_EQ(computeFactorial(1), 1);
}

void test_factorial_two() {
    ASSERT_EQ(computeFactorial(2), 2);
}

void test_factorial_three() {
    ASSERT_EQ(computeFactorial(3), 6);
}

void test_factorial_four() {
    ASSERT_EQ(computeFactorial(4), 24);
}

void test_factorial_five() {
    ASSERT_EQ(computeFactorial(5), 120);
}

void test_factorial_six() {
    ASSERT_EQ(computeFactorial(6), 720);
}

void test_factorial_large_number() {
    ASSERT_EQ(computeFactorial(10), 3628800);
}

void test_factorial_negative_number() {
    std::cout << "Note: test_factorial_negative_number not supported by this implementation.\n";
    ASSERT_TRUE(false);
}

void test_factorial_string_input() {
    std::cout << "Note: test_factorial_string_input not supported by this implementation.\n";
    ASSERT_TRUE(false);
}

int main() {
    test_factorial_zero();
    test_factorial_one();
    test_factorial_two();
    test_factorial_three();
    test_factorial_four();
    test_factorial_five();
    test_factorial_six();
    test_factorial_large_number();
    test_factorial_negative_number();
    test_factorial_string_input();

    std::cout << "\nTotal: " << tests_run << " tests run.\n";
    std::cout << "Passed: " << tests_passed << "\n";
    std::cout << "Failed: " << (tests_run - tests_passed) << "\n";

    return 0;
}
