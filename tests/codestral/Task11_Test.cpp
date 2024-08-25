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

#include "../../source/output/claude/cpp/Task11_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
 #include "../../source/output/codestral/cpp/Task11_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task11_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
#include "../../source/output/gpt4o/cpp/Task11_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task11_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function





// Function prototype
// int nbYear(int p0, double percent, int aug, int p){return nb_year(p0,percent,aug,p );}

void testLargePopulationIncrease() {
    // Test with a large initial population and growth, smaller increment
    assert(nbYear(1500, 5, 100, 5000) == 15);
}

void testSmallPercentLargeAugmentation() {
    // Test with a small growth percentage and large augmentation
    assert(nbYear(1500000, 2.5, 10000, 2000000) == 10);
}

void testZeroPercentGrowth() {
    // Test with zero percent growth but positive annual augmentation
    assert(nbYear(1000, 0, 100, 1500) == 5);
}

void testNoAugmentation() {
    // Test with a non-zero percent growth but no annual augmentation
    assert(nbYear(1000, 10, 0, 3000) == 12);//
}

void testExactPopulationMatch() {
    // Test where the population exactly matches the target population in one year
    assert(nbYear(1000, 20, 100, 1200) == 1);
}

void testMinimumInputValues() {
    // Test with minimum positive values
    assert(nbYear(1, 1, 1, 2) == 1);
}

void testHighPercentLowAugmentation() {
    // Test with high growth percentage and low augmentation
    assert(nbYear(100, 50, 1, 500) == 4);
}

void testHighAugmentationLowPercent() {
    // Test with high annual augmentation and low growth percentage
    assert(nbYear(100, 1, 100, 600) == 5);
}

void testLargeInitialPopulation() {
    // Test with a large initial population and small target population
    assert(nbYear(1000000, 1, 1, 500000) == 0);
}

void testNegativePercent() {
    // Test with a negative percent value, should handle as 0 percent effectively
    assert(nbYear(1000, -2, 50, 1200) == 8);//
}

int main() {
    testLargePopulationIncrease();
    testSmallPercentLargeAugmentation();
    testZeroPercentGrowth();
    testNoAugmentation();//
    testExactPopulationMatch();
    testMinimumInputValues();
    testHighPercentLowAugmentation();
    testHighAugmentationLowPercent();
    testLargeInitialPopulation();
    testNegativePercent();//

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}





