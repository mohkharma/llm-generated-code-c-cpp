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

//#include "../../source/output/claude/cpp/Task8_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task8_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task8_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
 #include "../../source/output/gpt4o/cpp/Task8_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task8_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function



void run_test_case(char array[], int size, char expected) {
    char result = findMissingLetter(array, size);
    assert(result == expected);
    std::cout << "Test passed for missing letter: " << result << std::endl;
}

int main() {
    // Test cases
    char test1[] = {'a', 'b', 'c', 'd', 'f'};
    run_test_case(test1, 5, 'e');

    char test2[] = {'b', 'c', 'd', 'f', 'g'};
    run_test_case(test2, 5, 'e');

    char test3[] = {'a', 'c', 'd', 'e', 'f', 'g'};
    run_test_case(test3, 6, 'b');

    char test4[] = {'O', 'Q', 'R', 'S'};
    run_test_case(test4, 4, 'P');

    char test5[] = {'C', 'D', 'E', 'G', 'H'};
    run_test_case(test5, 5, 'F');

    char test6[] = {'A', 'B', 'D', 'E', 'F', 'G'};
    run_test_case(test6, 6, 'C');

    char test7[] = {'a', 'b', 'd'};
    run_test_case(test7, 3, 'c');

    char test8[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'n'};
    run_test_case(test8, 13, 'm');

    char test9[] = {'X', 'Z'};
    run_test_case(test9, 2, 'Y');

    char test10[] = {'a', 'c'};
    run_test_case(test10, 2, 'b');

    std::cout << "All test cases passed successfully." << std::endl;
    return 0;
}