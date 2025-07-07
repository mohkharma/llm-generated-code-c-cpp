// Task177_Test.cpp

#include <iostream>
#include <vector>
#include <string>

#include "../../../source/output/gemini/cpp/Task193_GEMINI_gemini-1.5-pro-001.cpp"

void runTest(int testNumber, const std::vector<int>& input, bool expected) {
    Solution sol;
    std::vector<int> nums = input;
    bool result = sol.xorGame(nums);
    if (result == expected) {
        std::cout << "[✅] Test " << testNumber << " passed.\n";
    } else {
        std::cout << "[❌] Test " << testNumber << " failed.\n";
        std::cout << "   Input: [";
        for (size_t i = 0; i < input.size(); ++i) {
            std::cout << input[i];
            if (i < input.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
        std::cout << "   Expected: " << (expected ? "true" : "false") << "\n";
        std::cout << "   Got: " << (result ? "true" : "false") << "\n";
    }
}

int main() {
    runTest(1, {1, 1, 2}, false);
    runTest(2, {0, 1}, true);
    runTest(3, {1, 2, 3}, true);
    return 0;
}