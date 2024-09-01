#include <iostream>
#include <vector>
#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>

#include "../../source/output/claude/cpp/Task60_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task60_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task60_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task60_OPENAI_gpt-4o.cpp"  // Include the header for the function
//#include "../../source/output/llama-3/cpp/Task60_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function


void test_case(long long num, const std::string& expected) {
    std::string result = expanded_form(num);
    assert(result == expected && "Test case failed");
}

void test_two_digit_number() {
    // Test with a two-digit number
    test_case(12, "10 + 2");
}

void test_two_digit_number_with_zero() {
    // Test with a two-digit number that includes zero
    test_case(42, "40 + 2");
}

void test_five_digit_number() {
    // Test with a five-digit number
    test_case(70304, "70000 + 300 + 4");
}

void test_single_digit_number() {
    // Test with a single-digit number
    test_case(5, "5");
}

void test_number_with_zeros() {
    // Test with a number that includes zeros between significant digits
    test_case(1001, "1000 + 1");
}

void test_large_number() {
    // Test with a large number
    test_case(123456, "100000 + 20000 + 3000 + 400 + 50 + 6");
}

void test_number_with_repeated_digits() {
    // Test with a number with repeated digits
    test_case(2222, "2000 + 200 + 20 + 2");
}

void test_number_with_only_zeros_after_first_digit() {
    // Test with a number that has zeros after the first significant digit
    test_case(50000, "50000");
}

void test_number_with_only_zeros_before_last_digit() {
    // Test with a number that has zeros before the last digit
    test_case(10005, "10000 + 5");
}

void test_edge_case_smallest_number() {
    // Test with the smallest number greater than zero
    test_case(1, "1");
}

int main() {
    // Running all test cases
    test_two_digit_number();
    test_two_digit_number_with_zero();
    test_five_digit_number();
    test_single_digit_number();
    test_number_with_zeros();
    test_large_number();
    test_number_with_repeated_digits();
    test_number_with_only_zeros_after_first_digit();
    test_number_with_only_zeros_before_last_digit();
    test_edge_case_smallest_number();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}