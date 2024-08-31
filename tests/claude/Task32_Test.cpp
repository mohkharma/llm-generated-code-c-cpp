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

#include "../../source/output/claude/cpp/Task32_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task32_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task32_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task32_OPENAI_gpt-4o.cpp"  // Include the header for the function
//#include "../../source/output/llama-3/cpp/Task32_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function



void testExactThreeYears() {
    // Test case where it takes exactly 3 years to reach the desired sum
    assert(Solution::calculateYears(1000.00, 0.05, 0.18, 1100.00) == 3);
}

void testZeroYears() {
    // Test case where desired sum equals initial principal
    assert(Solution::calculateYears(1000.00, 0.05, 0.18, 1000.00) == 0);
}

void testSmallIncreaseOneYear() {
    // Test case where it takes exactly 1 year to reach the desired sum
    assert(Solution::calculateYears(1000.00, 0.05, 0.18, 1040.00) == 1);
}

void testLongTermInvestment() {
    // Test case where it takes many years to reach the desired sum
    assert(Solution::calculateYears(1000.00, 0.05, 0.18, 2000.00) == 18); //todo fix for all languages
}

void testNoTax() {
    // Test case where there is no tax on the interest
    assert(Solution::calculateYears(1000.00, 0.05, 0.00, 2000.00) == 15);
}

void testHighTax() {
    // Test case where the tax rate is high
    assert(Solution::calculateYears(1000.00, 0.05, 0.50, 2000.00) == 29); //todo fix for all languages
}

void testHighInterestLowTax() {

    // Test case with high interest and low tax rate
    assert(Solution::calculateYears(1000.00, 0.10, 0.10, 2000.00) == 9  ); //todo fix for all languages
}

void testLowInterestHighTax() {
    // Test case with low interest and high tax rate
    assert(Solution::calculateYears(1000.00, 0.02, 0.50, 2000.00) == 70);//todo fix for all languages
}

void testMinimalInterest() {
    // Test case where the interest rate is very small
    assert(Solution::calculateYears(1000.00, 0.005, 0.18, 2000.00) == 170);//todo fix for all languages
}

void testHighPrincipalAndDesiredSum() {
    // Test case where both the principal and desired sum are very large
    assert(Solution::calculateYears(1000000.00, 0.05, 0.18, 2000000.00) == 18);
}

int main() {
    // Run all the test cases
    testExactThreeYears();
    testZeroYears();
    testSmallIncreaseOneYear();
    testLongTermInvestment();
    testNoTax();
    testHighTax();
    testHighInterestLowTax();
    testLowInterestHighTax();
    testMinimalInterest();
    testHighPrincipalAndDesiredSum();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}