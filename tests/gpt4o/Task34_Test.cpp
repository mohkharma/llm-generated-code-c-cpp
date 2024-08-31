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
// #include "../../source/output/gemini/cpp/Task34_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
#include "../../source/output/gpt4o/cpp/Task34_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task34_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function


void testThreeDigitisNarcissistic() {
    // 153 is a known 3-digit isNarcissistic number
    assert(isNarcissistic(153) == true);
}

void testThreeDigitNonisNarcissistic() {
    // 123 is not a isNarcissistic number
    assert(isNarcissistic(123) == false);
}

void testFourDigitisNarcissistic() {
    // 1634 is a known 4-digit isNarcissistic number
    assert(isNarcissistic(1634) == true);
}

void testFourDigitNonisNarcissistic() {
    // 1652 is not a isNarcissistic number
    assert(isNarcissistic(1652) == false);
}

void testSingleDigitisNarcissistic() {
    // All single-digit numbers are isNarcissistic
    assert(isNarcissistic(5) == true);
}

void testLargeisNarcissisticNumber() {
    // 9474 is a known 4-digit isNarcissistic number
    assert(isNarcissistic(9474) == true);
}

void testLargeNonisNarcissisticNumber() {
    // 9475 is not a isNarcissistic number
    assert(isNarcissistic(9475) == false);
}

void testFiveDigitisNarcissistic() {
    // 54748 is a known 5-digit isNarcissistic number
    assert(isNarcissistic(54748) == true);
}

void testFiveDigitNonisNarcissistic() {
    // 12345 is not a isNarcissistic number
    assert(isNarcissistic(12345) == false);
}

void testEdgeCaseSingleDigitOne() {
    // 1 is a isNarcissistic number
    assert(isNarcissistic(1) == true);
}

int main() {
    // Run all the test cases
    testThreeDigitisNarcissistic();
    testThreeDigitNonisNarcissistic();
    testFourDigitisNarcissistic();
    testFourDigitNonisNarcissistic();
    testSingleDigitisNarcissistic();
    testLargeisNarcissisticNumber();
    testLargeNonisNarcissisticNumber();
    testFiveDigitisNarcissistic();
    testFiveDigitNonisNarcissistic();
    testEdgeCaseSingleDigitOne();

    // If no assertion failed
    std::cout << "All tests passed!" << std::endl;

    return 0;
}