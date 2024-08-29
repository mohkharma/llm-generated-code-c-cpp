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

// #include "../../source/output/claude/cpp/Task26_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task26_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task26_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task26_OPENAI_gpt-4o.cpp"  // Include the header for the function
#include "../../source/output/llama-3/cpp/Task26_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function

void testSingleElement() {
    std::vector<int> arr = {7};
    assert(findOdd(arr) == 7);
}

void testSingleZero() {
    std::vector<int> arr = {0};
    assert(findOdd(arr) == 0);
}

void testOddOccurrence() {
    std::vector<int> arr = {1, 1, 2};
    assert(findOdd(arr) == 2);
}

void testMultipleOccurrencesOfOdd() {
    std::vector<int> arr = {0, 1, 0, 1, 0};
    assert(findOdd(arr) == 0);
}

void testLargeArrayWithSingleOddOccurrence() {
    std::vector<int> arr = {1, 2, 2, 3, 3, 3, 4, 3, 3, 3, 2, 2, 1};
    assert(findOdd(arr) == 4);
}

void testNegativeNumbers() {
    std::vector<int> arr = {-1, -1, -2, -2, -3};
    assert(findOdd(arr) == -3);
}

void testAllOddOccurrences() {
    std::vector<int> arr = {5, 5, 5,  7, 7, 9 ,9};
    assert(findOdd(arr) == 5);
}

void testAllEvenOccurrences() {
    std::vector<int> arr = {7, 7, 8, 8, 9, 9, 10};
    assert(findOdd(arr) == 10);
}

void testRepeatedElementAtEnd() {
    std::vector<int> arr = {1, 1, 2, 2, 3, 3, 9, 9, 9};
    assert(findOdd(arr) == 9);
}

void testMultipleElementsWithOneOdd() {
    std::vector<int> arr = {2, 2, 3, 3, 4, 4, 5, 5, 5};
    assert(findOdd(arr) == 5);
}

// Main function to run all tests
int main() {
    testSingleElement();
    testSingleZero();
    testOddOccurrence();
    testMultipleOccurrencesOfOdd();
    testLargeArrayWithSingleOddOccurrence();
    testNegativeNumbers();
    testAllOddOccurrences();
    testAllEvenOccurrences();
    testRepeatedElementAtEnd();
    testMultipleElementsWithOneOdd();

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}