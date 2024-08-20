#include <iostream>
#include <vector>
#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cassert>


//#include "../../source/output/claude/cpp/Task5_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task5_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task5_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
 #include "../../source/output/gpt4o/cpp/Task5_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task5_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function



// Function to run a test case and track the number of passed tests
void run_test_case(long long num, int expected, int &passed_tests) {
    int result = persistence(num);
    assert(result == expected);  // Ensure the result matches the expected value
    if (result == expected) {
        passed_tests++;
    }
}

int main() {
    int total_tests = 10;
    int passed_tests = 0;

    // Test Case 1: 3 steps needed (Example: 39 -> 27 -> 14 -> 4)
    run_test_case(39, 3, passed_tests);

    // Test Case 2: 4 steps needed (Example: 999 -> 729 -> 126 -> 12 -> 2)
    run_test_case(999, 4, passed_tests);

    // Test Case 3: No steps needed (Single digit)
    run_test_case(4, 0, passed_tests);

    // Test Case 4: 2 steps needed (Example: 25 -> 10 -> 0)
    run_test_case(25, 2, passed_tests);

    // Test Case 5: 4 steps needed (Example: 77 -> 49 -> 36 -> 18 -> 8)
    run_test_case(77, 4, passed_tests);

    // Test Case 6: No steps needed (Single digit)
    run_test_case(8, 0, passed_tests);

    // Test Case 7: 1 step needed (Example: 10 -> 0)
    run_test_case(10, 1, passed_tests);

    // Test Case 8: 1 step needed (Example: 123 -> 6)
    run_test_case(123, 1, passed_tests);

    // Test Case 9: 6 steps needed (Example: 6788 -> 2688 -> 768 -> 336 -> 54 -> 20 -> 0)
    run_test_case(6788, 6, passed_tests);

    // Test Case 10: 1 step needed (Example: 9909 -> 0)
    run_test_case(9909, 1, passed_tests);

    // Calculate and print success percentage
    double success_percentage = (static_cast<double>(passed_tests) / total_tests) * 100.0;
    std::cout << "Passed " << passed_tests << " out of " << total_tests << " tests.\n";
    std::cout << "Success rate: " << success_percentage << "%\n";

    return 0;
}
