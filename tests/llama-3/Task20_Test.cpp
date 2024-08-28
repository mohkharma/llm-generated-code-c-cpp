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

// #include "../../source/output/claude/cpp/Task20_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task20_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task20_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task20_OPENAI_gpt-4o.cpp"  // Include the header for the function
#include "../../source/output/llama-3/cpp/Task20_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function



void testBasicExample1() {
    assert(digPow(89, 1) == 1);
    std::cout << "Test Basic Example 1 passed!\n";
}

void testBasicExample2() {
    assert(digPow(92, 1) == -1);
    std::cout << "Test Basic Example 2 passed!\n";
}

void testBasicExample3() {
    assert(digPow(695, 2) == 2);
    std::cout << "Test Basic Example 3 passed!\n";
}

void testNoSolution() {
    assert(digPow(123, 2) == -1);
    std::cout << "Test No Solution passed!\n";
}

void testSingleDigit() {
    assert(digPow(5, 1) == 1);
    std::cout << "Test Single Digit passed!\n";
}

void testConsecutivePowers() {
    assert(digPow(135, 1) == 1);
    std::cout << "Test Consecutive Powers passed!\n";
}

void testLargerValue() {
    assert(digPow(1000, 2) == -1);
    std::cout << "Test Larger Value passed!\n";
}

void testAnotherExample() {
    assert(digPow(135, 2) == -1);
    std::cout << "Test Another Example passed!\n";
}

void testAllDigitsSame() {
    assert(digPow(111, 1) == -1);
    std::cout << "Test All Digits Same passed!\n";
}

void testLeadingZeros() {
    // Leading zeros don't typically appear in integer values,
    // but for the sake of an edge case, this would handle the value as-is.
    assert(digPow(100, 1) == -1);
    std::cout << "Test Leading Zeros passed!\n";
}

int main() {
    testBasicExample1();
    testBasicExample2();
    testBasicExample3();
    testNoSolution();
    testSingleDigit();
    testConsecutivePowers();
    testLargerValue();
    testAnotherExample();
    testAllDigitsSame();
    testLeadingZeros();

    std::cout << "All tests passed!\n";
    return 0;
}