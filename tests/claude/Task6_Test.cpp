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

#include "../../source/output/claude/cpp/Task6_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task6_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task6_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task6_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task6_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function


void run_test_case(const std::vector<double> &arr, double expected) {
    double result = findUniq(arr);
    assert(result == expected);
    std::cout << "Test passed for unique number: " << result << std::endl;
}

int main() {
    run_test_case({1, 1, 1, 2, 1, 1}, 2.0);
    run_test_case({0, 0, 0.55, 0, 0}, 0.55);
    run_test_case({3, 10, 3, 3, 3}, 10.0);
    run_test_case({7, 7, 7, 7, 3}, 3.0);
    run_test_case({0, 0, 0, 0, -1}, -1.0);
    run_test_case({9, 1, 9, 9, 9}, 1.0);
    run_test_case({6, 5, 6, 6, 6}, 5.0);
    run_test_case({100000, 100000, 100000, 999999}, 999999.0);
    run_test_case({-10, -10, -10, -1}, -1.0);
    run_test_case({99.9, 99.9, 0.1, 99.9}, 0.1);

    std::cout << "All test cases passed successfully." << std::endl;
    return 0;
}