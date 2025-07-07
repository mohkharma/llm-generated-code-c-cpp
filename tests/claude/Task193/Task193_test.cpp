
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "../../../source/output/claude/cpp/Task193_CLAUDE_claude-3-5-sonnet-20240620.cpp"

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
    runTest(4, {0}, true);             // xor = 0 → Alice wins
    runTest(5, {5, 5, 5}, false);      // xor != 0 and odd length
    runTest(6, {4, 4}, true);          // xor = 0 → Alice wins
    runTest(7, {1, 1, 1, 1}, true);    // xor = 0 → Alice wins
    return 0;
}
