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

#include "../../source/output/claude/cpp/Task8_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task8_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task8_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task8_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task8_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function


void run_test_case(std::vector<char> chars, char expected) {
    char result = findMissingLetter(chars);
    assert(result == expected);
    std::cout << "Test passed for missing letter: " << result << std::endl;
}

int main() {
    run_test_case({'a', 'b', 'c', 'd', 'f'}, 'e');
    run_test_case({'b', 'c', 'd', 'f', 'g'}, 'e');
    run_test_case({'a', 'c', 'd', 'e', 'f', 'g'}, 'b');
    run_test_case({'O', 'Q', 'R', 'S'}, 'P');
    run_test_case({'C', 'D', 'E', 'G', 'H'}, 'F');
    run_test_case({'A', 'B', 'D', 'E', 'F', 'G'}, 'C');
    run_test_case({'a', 'b', 'd'}, 'c');
    run_test_case({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'n'}, 'm');
    run_test_case({'X', 'Z'}, 'Y');
    run_test_case({'a', 'c'}, 'b');

    std::cout << "All test cases passed successfully." << std::endl;
    return 0;
}