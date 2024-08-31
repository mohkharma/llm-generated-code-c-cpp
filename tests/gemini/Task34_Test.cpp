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

// #include "../../source/output/claude/cpp/Task34_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task34_MISTRAL_codestral-latest.cpp"  // Include the header for the function
#include "../../source/output/gemini/cpp/Task34_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task34_OPENAI_gpt-4o.cpp"  // Include the header for the function
//#include "../../source/output/llama-3/cpp/Task34_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function


void testThreeDigitNarcissistic() {
    // 153 is a known 3-digit Narcissistic number
    assert(narcissistic(153) == true);
}

void testThreeDigitNonNarcissistic() {
    // 123 is not a Narcissistic number
    assert(narcissistic(123) == false);
}

void testFourDigitNarcissistic() {
    // 1634 is a known 4-digit Narcissistic number
    assert(narcissistic(1634) == true);
}

void testFourDigitNonNarcissistic() {
    // 1652 is not a Narcissistic number
    assert(narcissistic(1652) == false);
}

void testSingleDigitNarcissistic() {
    // All single-digit numbers are Narcissistic
    assert(narcissistic(5) == true);
}

void testLargeNarcissisticNumber() {
    // 9474 is a known 4-digit Narcissistic number
    assert(narcissistic(9474) == true);
}

void testLargeNonNarcissisticNumber() {
    // 9475 is not a Narcissistic number
    assert(narcissistic(9475) == false);
}

void testFiveDigitNarcissistic() {
    // 54748 is a known 5-digit Narcissistic number
    assert(narcissistic(54748) == true);
}

void testFiveDigitNonNarcissistic() {
    // 12345 is not a Narcissistic number
    assert(narcissistic(12345) == false);
}

void testEdgeCaseSingleDigitOne() {
    // 1 is a Narcissistic number
    assert(narcissistic(1) == true);
}

int main() {
    // Run all the test cases
    testThreeDigitNarcissistic();
    testThreeDigitNonNarcissistic();
    testFourDigitNarcissistic();
    testFourDigitNonNarcissistic();
    testSingleDigitNarcissistic();
    testLargeNarcissisticNumber();
    testLargeNonNarcissisticNumber();
    testFiveDigitNarcissistic();
    testFiveDigitNonNarcissistic();
    testEdgeCaseSingleDigitOne();

    // If no assertion failed
    std::cout << "All tests passed!" << std::endl;

    return 0;
}