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

//#include "../../source/output/claude/cpp/Task25_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
 #include "../../source/output/codestral/cpp/Task25_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task25_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task25_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task25_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function

void testNumbering() {
    // Test Case 1
    std::vector<std::string> input1 = {};
    std::vector<std::string> expected1 = {};
    assert(number(input1) == expected1);
    std::cout << "Test Case 1 passed!" << std::endl;

    // Test Case 2
    std::vector<std::string> input2 = {"Hello"};
    std::vector<std::string> expected2 = {"1: Hello"};
    assert(number(input2) == expected2);
    std::cout << "Test Case 2 passed!" << std::endl;

    // Test Case 3
    std::vector<std::string> input3 = {"Hello", "World"};
    std::vector<std::string> expected3 = {"1: Hello", "2: World"};
    assert(number(input3) == expected3);
    std::cout << "Test Case 3 passed!" << std::endl;

    // Test Case 4
    std::vector<std::string> input4 = {"a", "b", "c"};
    std::vector<std::string> expected4 = {"1: a", "2: b", "3: c"};
    assert(number(input4) == expected4);
    std::cout << "Test Case 4 passed!" << std::endl;

    // Test Case 5
    std::vector<std::string> input5 = {"This is a long line", "Another long line"};
    std::vector<std::string> expected5 = {"1: This is a long line", "2: Another long line"};
    assert(number(input5) == expected5);
    std::cout << "Test Case 5 passed!" << std::endl;

    // Test Case 6
    std::vector<std::string> input6 = {"Line 1", "", "Line 3"};
    std::vector<std::string> expected6 = {"1: Line 1", "2: ", "3: Line 3"};
    assert(number(input6) == expected6);
    std::cout << "Test Case 6 passed!" << std::endl;

    // Test Case 7
    std::vector<std::string> input7 = {"!@#$%^", "&*()_+", "[]{}"};
    std::vector<std::string> expected7 = {"1: !@#$%^", "2: &*()_+", "3: []{}"};
    assert(number(input7) == expected7);
    std::cout << "Test Case 7 passed!" << std::endl;

    // Test Case 8
    std::vector<std::string> input8 = {"123", "456", "789"};
    std::vector<std::string> expected8 = {"1: 123", "2: 456", "3: 789"};
    assert(number(input8) == expected8);
    std::cout << "Test Case 8 passed!" << std::endl;

    // Test Case 9
    std::vector<std::string> input9 = {"  leading", "trailing  ", "  both  "};
    std::vector<std::string> expected9 = {"1:   leading", "2: trailing  ", "3:   both  "};
    assert(number(input9) == expected9);
    std::cout << "Test Case 9 passed!" << std::endl;

    // Test Case 10
    std::vector<std::string> input10;
    std::vector<std::string> expected10;
    for (int i = 0; i < 1000; ++i) {
        input10.push_back("line " + std::to_string(i));
        expected10.push_back(std::to_string(i + 1) + ": line " + std::to_string(i));
    }
    assert(number(input10) == expected10);
    std::cout << "Test Case 10 passed!" << std::endl;
}

int main() {
    testNumbering();
    std::cout << "All test cases passed!" << std::endl;
    return 0;
}