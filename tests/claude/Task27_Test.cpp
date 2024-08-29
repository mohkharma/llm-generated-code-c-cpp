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

#include "../../source/output/claude/cpp/Task27_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task27_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task27_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task27_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task27_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function


// Test cases
void runTests() {
    // Test Case 1
    std::vector<int> input1 = {2, 4, 0, 100, 4, 11, 2602, 36};
    int expected1 = 11;
    assert(findOutlier(input1) == expected1);
    std::cout << "Test Case 1 passed!\n";

    // Test Case 2
    std::vector<int> input2 = {160, 3, 1719, 19, 11, 13, -21};
    int expected2 = 160;
    assert(findOutlier(input2) == expected2);
    std::cout << "Test Case 2 passed!\n";

    // Test Case 3
    std::vector<int> input3 = {1, 3, 5, 7, 8}; // Only 8 is even
    int expected3 = 8;
    assert(findOutlier(input3) == expected3);
    std::cout << "Test Case 3 passed!\n";

    // Test Case 4
    std::vector<int> input4 = {2, 4, 6, 8, 10, 13}; // Only 13 is odd
    int expected4 = 13;
    assert(findOutlier(input4) == expected4);
    std::cout << "Test Case 4 passed!\n";

    // Test Case 5
    std::vector<int> input5 = {10, 12, 14, 16, 18, 21, 22}; // Only 21 is odd
    int expected5 = 21;
    assert(findOutlier(input5) == expected5);
    std::cout << "Test Case 5 passed!\n";

    // Test Case 6
    std::vector<int> input6 = {1, 2, 3}; // Only 2 is even
    int expected6 = 2;
    assert(findOutlier(input6) == expected6);
    std::cout << "Test Case 6 passed!\n";

    // Test Case 7
    std::vector<int> input7 = {3, 5, 7, 11, 2}; // Only 2 is even among odds
    int expected7 = 2;
    assert(findOutlier(input7) == expected7);
    std::cout << "Test Case 7 passed!\n";

    // Test Case 8
    std::vector<int> input8 = {2, 2, 2, 2, 1}; // Only 1 is odd
    int expected8 = 1;
    assert(findOutlier(input8) == expected8);
    std::cout << "Test Case 8 passed!\n";

    // Test Case 9
    std::vector<int> input9 = {11, 13, 15, 17, 19, 20}; // Only 20 is even
    int expected9 = 20;
    assert(findOutlier(input9) == expected9);
    std::cout << "Test Case 9 passed!\n";

    // Test Case 10
    std::vector<int> input10 = {4, 8, 12, 16, 20, 21, 24}; // Only 21 is odd
    int expected10 = 21;
    assert(findOutlier(input10) == expected10);
    std::cout << "Test Case 10 passed!\n";
}

int main() {
    runTests();
    std::cout << "All test cases passed!\n";
    return 0;
}