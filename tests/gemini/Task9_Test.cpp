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

//#include "../../source/output/claude/cpp/Task9_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task9_MISTRAL_codestral-latest.cpp"  // Include the header for the function
 #include "../../source/output/gemini/cpp/Task9_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task9_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task9_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function


void testEmptyArray() {
 assert(Solution::oddOrEven({}) == "even");
}

void testSinglePositiveOdd() {
 assert(Solution::oddOrEven({7}) == "odd");
}

void testSinglePositiveEven() {
 assert(Solution::oddOrEven({8}) == "even");
}

void testMultiplePositives() {
 assert(Solution::oddOrEven({1, 3, 5, 7}) == "even");
}

void testMultiplePositivesOddSum() {
 assert(Solution::oddOrEven({1, 2, 3, 4}) == "even");
}

void testMultipleNegatives() {
 assert(Solution::oddOrEven({-2, -4, -6}) == "even");
}

void testMultipleNegativesOddSum() {
 assert(Solution::oddOrEven({-1, -2, -3}) == "even");
}

void testMixedNumbersEvenSum() {
 assert(Solution::oddOrEven({1, -1, 2, -2}) == "even");
}

void testMixedNumbersOddSum() {
 assert(Solution::oddOrEven({1, -1, 2}) == "even");
}

void testLargeNumbers() {
 assert(Solution::oddOrEven({1000000, 2000000, -3000000}) == "even");
}

int main() {
 testEmptyArray();
 testSinglePositiveOdd();
 testSinglePositiveEven();
 testMultiplePositives();
 testMultiplePositivesOddSum();
 testMultipleNegatives();
 testMultipleNegativesOddSum();
 testMixedNumbersEvenSum();
 testMixedNumbersOddSum();
 testLargeNumbers();

 std::cout << "All test cases passed!" << std::endl;
 return 0;
}