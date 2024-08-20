#include <iostream>
#include <vector>
#include <cassert>
// #include "../../source/output/claude/cpp/Task2_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
//#include "../../source/output/codestral/cpp/Task2_MISTRAL_codestral-latest.cpp"  // Include the header for the function
#include "../../source/output/gemini/cpp/Task2_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task1_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task1_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function

// Helper function to run a test case
void run_test_case(const int input[10], const std::string& expected, const std::string& test_name) {
    std::string result = createPhoneNumber(input);
    assert(result == expected && "Test case failed");
    std::cout << test_name << " passed: " << result << std::endl;
}

int main() {
    // Test Case 1: Normal case
    int input1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    run_test_case(input1, "(123) 456-7890", "Normal case");

    // Test Case 2: All zeros
    int input2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    run_test_case(input2, "(000) 000-0000", "All zeros");

    // Test Case 3: All nines
    int input3[] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    run_test_case(input3, "(999) 999-9999", "All nines");

    // Test Case 4: Alternating digits
    int input4[] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
    run_test_case(input4, "(101) 010-1010", "Alternating digits");

    // Test Case 5: Ascending order
    int input5[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    run_test_case(input5, "(012) 345-6789", "Ascending order");

    // Test Case 6: Descending order
    int input6[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    run_test_case(input6, "(987) 654-3210", "Descending order");

    // Test Case 7: Repeated digits
    int input7[] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 3};
    run_test_case(input7, "(111) 222-3333", "Repeated digits");

    // Test Case 8: Random mix
    int input8[] = {5, 2, 9, 3, 7, 1, 0, 8, 6, 4};
    run_test_case(input8, "(529) 371-0864", "Random mix");

    // Test Case 9: Another random mix
    int input9[] = {7, 4, 2, 8, 5, 0, 9, 1, 3, 6};
    run_test_case(input9, "(742) 850-9136", "Another random mix");

    // Test Case 10: Edge case (all same digit except one)
    int input10[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 2};
    run_test_case(input10, "(111) 111-1112", "Edge case (all same digit except one)");

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}