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

#include "../../source/output/claude/cpp/Task10_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task10_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task10_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task10_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task10_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function

// Function prototype
int getSum(int a, int b){return Solution::getSum(a,b);}

void testPositiveRange() {
    // Test with positive numbers where a < b
    assert(getSum(1, 2) == 3);
}

void testPositiveRangeReversed() {
    // Test with positive numbers where b < a
    assert(getSum(2, 1) == 3);
}

void testSingleNumber() {
    // Test with a single number
    assert(getSum(5, 5) == 5);
}

void testZeroInRange() {
    // Test with a range that includes zero
    assert(getSum(0, 1) == 1);
}

void testNegativeToPositive() {
    // Test with a range from negative to positive numbers
    assert(getSum(-1, 2) == 2);
}

void testNegativeRange() {
    // Test with negative numbers where a < b
    assert(getSum(-3, -1) == -6);
}

void testNegativeRangeReversed() {
    // Test with negative numbers where b < a
    assert(getSum(-1, -3) == -6);
}

void testPositiveAndNegativeRange() {
    // Test with a mix of positive and negative numbers where a < b
    assert(getSum(-2, 1) == -2);
}

void testPositiveAndNegativeRangeReversed() {
    // Test with a mix of positive and negative numbers where b < a
    assert(getSum(1, -2) == -2);
}

void testLargeRange() {
    // Test with a large range from -100 to 100
    assert(getSum(-100, 100) == 0);
}

int main() {
    testPositiveRange();
    testPositiveRangeReversed();
    testSingleNumber();
    testZeroInRange();
    testNegativeToPositive();
    testNegativeRange();
    testNegativeRangeReversed();
    testPositiveAndNegativeRange();
    testPositiveAndNegativeRangeReversed();
    testLargeRange();

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}
