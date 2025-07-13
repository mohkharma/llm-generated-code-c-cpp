// Task183_Test.cpp

#include <iostream>
#include <string>
#include "../../../source/output/llama-3/cpp/Task183_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"
void runTest(const std::string& input, int span, int expected, int caseNumber, bool& allPassed) {
    int actual = largestProduct(input, span);
    if (actual != expected) {
        std::cout << "❌ Test Case " << caseNumber << " Failed!\n";
        std::cout << "   Input: \"" << input << "\", Span: " << span << "\n";
        std::cout << "   Expected: " << expected << ", Got: " << actual << "\n";
        allPassed = false;
    }
}

int main() {
    bool allPassed = true;

    runTest("63915", 3, 162, 1, allPassed);
    runTest("123456789", 2, 72, 2, allPassed);
    runTest("00000", 3, 0, 3, allPassed);
    runTest("987654321", 4, 3024, 4, allPassed);
    runTest("11111", 5, 1, 5, allPassed);
    runTest("123", 1, 3, 6, allPassed);
    runTest("99999", 5, 59049, 7, allPassed);
    runTest("56789", 2, 72, 8, allPassed);
    runTest("1234567890", 5, 15120, 9, allPassed);
    runTest("1", 1, 1, 10, allPassed);

    if (allPassed) {
        std::cout << "✅ All test cases passed!\n";
    }

    return 0;
}
