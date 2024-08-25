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

// #include "../../source/output/claude/cpp/Task16_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task16_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task16_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
#include "../../source/output/gpt4o/cpp/Task16_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task16_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function




// Function to test the solution
void runTest(const char* str, const char* ending, bool expected, const char* testName) {
    bool result = solution(str, ending);
    if (result == expected) {
        printf("[PASS] %s\n", testName);
    } else {
        printf("[FAIL] %s: Expected %s but got %s\n", testName, expected ? "true" : "false", result ? "true" : "false");
    }
}

int main() {
    // Test cases
    runTest("abc", "bc", true, "testBasicTrue");
    runTest("abc", "d", false, "testBasicFalse");
    runTest("abc", "", true, "testEmptyEnding");
    runTest("", "a", false, "testEmptyString");
    runTest("hello", "hello", true, "testEndingIsMainString");
    runTest("short", "longerEnding", false, "testEndingLongerThanMainString");
    runTest("startmiddleend", "start", false, "testEndingAtStart");
    runTest("substring", "str", false, "testEndingIsSubstring");
    runTest("HELLO", "hello", false, "testCaseSensitiveEnding");
    runTest("testtesttest", "test", true, "testMultipleOccurrences");

    return 0;
}
