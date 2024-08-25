#include <iostream>
#include <vector>
#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cassert>


#include "../../source/output/claude/cpp/Task4_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function

// #include "../../source/output/codestral/cpp/Task4_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task4_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task4_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task4_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function


void run_test_case(const std::string& input, bool expected, const std::string& test_name) {
    bool result = is_isogram(input);
    assert(result == expected && "Test case failed");
    std::cout << test_name << " passed: " << std::boolalpha << result << std::endl;
}

int main() {
    // Test Case 1: Basic isogram test
    run_test_case("Dermatoglyphics", true, "Test Case 1");

    // Test Case 2: Repeating letter
    run_test_case("aba", false, "Test Case 2");

    // Test Case 3: Case-insensitive repeating letter
    run_test_case("moOse", false, "Test Case 3");

    // Test Case 4: All lowercase isogram
    run_test_case("isogram", true, "Test Case 4");

    // Test Case 5: Mixed case isogram
    run_test_case("Machine", true, "Test Case 5");

    // Test Case 6: Edge case - Empty string
    run_test_case("", true, "Test Case 6");

    // Test Case 7: Consecutive repeating letter
    run_test_case("letter", false, "Test Case 7");

    // Test Case 8: Multiple repeating letters
    run_test_case("Bookkeeper", false, "Test Case 8");

    // Test Case 9: No repeating letters, mixed case
    run_test_case("Alphabet", false, "Test Case 9");

    // Test Case 10: Edge case - String with hyphen
    run_test_case("a-c", false, "Test Case 10");

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}