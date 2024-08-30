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

// #include "../../source/output/claude/cpp/Task22_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task22_MISTRAL_codestral-latest.cpp"  // Include the header for the function
#include "../../source/output/gemini/cpp/Task22_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task22_OPENAI_gpt-4o.cpp"  // Include the header for the function
 // #include "../../source/output/llama-3/cpp/Task22_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function


////the program only accept string unlike the question desciption
// void testMixedList() {
//     // Test with a list containing integers and strings
//     std::vector<std::string>  input = {1, 2, "a", "b"};
//     std::vector<int> expected = {1, 2};
//     assert(filter_list(input) == expected);
//     std::cout << "testMixedList passed.\n";
// }
//
// void testEmptyList() {
//     // Test with an empty list
//     std::vector<std::string>  input = {};
//     std::vector<int> expected = {};
//     assert(filter_list(input) == expected);
//     std::cout << "testEmptyList passed.\n";
// }
//
// void testAllStrings() {
//     // Test with a list containing only strings
//     std::vector<std::string>  input = {"a", "b", "c"};
//     std::vector<int> expected = {};
//     assert(filter_list(input) == expected);
//     std::cout << "testAllStrings passed.\n";
// }
//
// void testAllIntegers() {
//     // Test with a list containing only integers
//     std::vector<std::string>  input = {1, 2, 3, 4};
//     std::vector<int> expected = {1, 2, 3, 4};
//     assert(filter_list(input) == expected);
//     std::cout << "testAllIntegers passed.\n";
// }
//
// void testStringsAndIntegersMixed() {
//     // Test with a list of mixed strings and integers with varied content
//     std::vector<std::string>  input = {1, "a", 2, "b", 0, 15};
//     std::vector<int> expected = {1, 2, 0, 15};
//     assert(filter_list(input) == expected);
//     std::cout << "testStringsAndIntegersMixed passed.\n";
// }
//
// void testSingleElementInteger() {
//     // Test with a list containing a single integer
//     std::vector<std::string>  input = {5};
//     std::vector<int> expected = {5};
//     assert(filter_list(input) == expected);
//     std::cout << "testSingleElementInteger passed.\n";
// }
//
// void testSingleElementString() {
//     // Test with a list containing a single string
//     std::vector<std::string>  input = {"onlyString"};
//     std::vector<int> expected = {};
//     assert(filter_list(input) == expected);
//     std::cout << "testSingleElementString passed.\n";
// }
//
// void testIntegersAndNumericStrings() {
//     // Test with a list containing integers and numeric strings
//     std::vector<std::string>  input = {1, "2", "three", 4, "5"};
//     std::vector<int> expected = {1, 4};
//     assert(filter_list(input) == expected);
//     std::cout << "testIntegersAndNumericStrings passed.\n";
// }
//
// void testNegativeIntegers() {
//     // Test with a list containing negative integers and strings
//     std::vector<std::string>  input = {1, "-2", 3, "4"};
//     std::vector<int> expected = {1, 3};
//     assert(filter_list(input) == expected);
//     std::cout << "testNegativeIntegers passed.\n";
// }
//
// void testLargeList() {
//     // Test with a large list of integers and strings
//     std::vector<std::string>  input = {
//         100, "200", 300, "400", 500, "600", 700, "800", 900, "1000",
//         1100, "1200", 1300, "1400", 1500, "1600", 1700, "1800", 1900, "2000"
//     };
//     std::vector<int> expected = {
//         100, 300, 500, 700, 900, 1100, 1300, 1500, 1700, 1900
//     };
//     assert(filter_list(input) == expected);
//     std::cout << "testLargeList passed.\n";
// }
//
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
//     std::cout << "All tests passed!\n";
//     return 0;
// }