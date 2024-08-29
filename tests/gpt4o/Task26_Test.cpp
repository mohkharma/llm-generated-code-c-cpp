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

//#include "../../source/output/claude/cpp/Task26_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task26_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task26_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
 #include "../../source/output/gpt4o/cpp/Task26_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task26_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function

void testSingleElement() {
    int arr[] = {7};
    assert(findOddOccurrence(arr,1) == 7);
}

void testSingleZero() {
    int arr[] = {0};
    assert(findOddOccurrence(arr,1) == 0);
}

void testOddOccurrence() {
    int arr[] = {1, 1, 2};
    assert(findOddOccurrence(arr,3) == 2);
}

void testMultipleOccurrencesOfOdd() {
    int arr[] = {0, 1, 0, 1, 0};
    assert(findOddOccurrence(arr,5) == 0);
}

void testLargeArrayWithSingleOddOccurrence() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 3, 3, 3, 2, 2, 1};
    assert(findOddOccurrence(arr,13) == 4);
}

void testNegativeNumbers() {
    int arr[] = {-1, -1, -2, -2, -3};
    assert(findOddOccurrence(arr,5) == -3);
}

void testAllOddOccurrences() {
    int arr[] = {5, 5,5, 7, 7, 7,7, 9, 9};
    assert(findOddOccurrence(arr,9) == 5);
}

void testAllEvenOccurrences() {
    int arr[] = {7, 7, 8, 8, 9, 9, 10};
    assert(findOddOccurrence(arr,7) == 10);
}

void testRepeatedElementAtEnd() {
    int arr[] = {1, 1, 2, 2, 3, 3, 9, 9, 9};
    assert(findOddOccurrence(arr,9) == 9);
}

void testMultipleElementsWithOneOdd() {
    int arr[] = {2, 2, 3, 3, 4, 4, 5, 5, 5};
    assert(findOddOccurrence(arr,9) == 5);
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