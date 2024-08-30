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

#include "../../source/output/claude/cpp/Task22_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task22_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task22_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task22_OPENAI_gpt-4o.cpp"  // Include the header for the function
 // #include "../../source/output/llama-3/cpp/Task22_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function

//the program only accept int unlike the question desciption
// void testMixedList() {
//     const std::vector<int> input = {1, 2, "a", "b"};
//     std::vector<int> expected = {1, 2};
//     assert(Solution::filterList(input) == expected);
// }
//
// void testEmptyList() {
//     std::vector<std::any> input = {};
//     std::vector<int> expected = {};
//     assert(Solution::filterList(input) == expected);
// }
//
// void testAllStrings() {
//     std::vector<std::any> input = {"a", "b", "c"};
//     std::vector<int> expected = {};
//     assert(Solution::filterList(input) == expected);
// }
//
// void testAllIntegers() {
//     std::vector<std::any> input = {1, 2, 3, 4};
//     std::vector<int> expected = {1, 2, 3, 4};
//     assert(Solution::filterList(input) == expected);
// }
//
// void testStringsAndIntegersMixed() {
//     std::vector<std::any> input = {1, "a", 2, "b", 0, 15};
//     std::vector<int> expected = {1, 2, 0, 15};
//     assert(Solution::filterList(input) == expected);
// }
//
// void testSingleElementInteger() {
//     std::vector<std::any> input = {5};
//     std::vector<int> expected = {5};
//     assert(Solution::filterList(input) == expected);
// }
//
// void testSingleElementString() {
//     std::vector<std::any> input = {"onlyString"};
//     std::vector<int> expected = {};
//     assert(Solution::filterList(input) == expected);
// }
//
// void testIntegersAndNumericStrings() {
//     std::vector<std::any> input = {1, "2", "three", 4, "5"};
//     std::vector<int> expected = {1, 4};
//     assert(Solution::filterList(input) == expected);
// }
//
// void testNegativeIntegers() {
//     std::vector<std::any> input = {-1, "-2", 3, "4"};
//     std::vector<int> expected = {-1, 3};
//     assert(Solution::filterList(input) == expected);
// }
//
// void testLargeList() {
//     std::vector<std::any> input = {
//         100, "200", 300, "400", 500, "600", 700, "800", 900, "1000",
//         1100, "1200", 1300, "1400", 1500, "1600", 1700, "1800", 1900, "2000"
//     };
//     std::vector<int> expected = {
//         100, 300, 500, 700, 900, 1100, 1300, 1500, 1700, 1900
//     };
//     assert(Solution::filterList(input) == expected);
// }
//
// // Main function to run all tests
// int main() {
//     testMixedList();
//     testEmptyList();
//     testAllStrings();
//     testAllIntegers();
//     testStringsAndIntegersMixed();
//     testSingleElementInteger();
//     testSingleElementString();
//     testIntegersAndNumericStrings();
//     testNegativeIntegers();
//     testLargeList();
//
//     std::cout << "All test cases passed!" << std::endl;
//     return 0;
// }