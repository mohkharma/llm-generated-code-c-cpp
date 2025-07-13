#include <iostream>
#include <string>
#include "../../../source/output/gemini/cpp/Task191_GEMINI_gemini-1.5-pro-001.cpp"

using namespace std;

void runTest(const string& input, int expected, int& passed, int& total) {
    total++;
    Solution solution;
    int result = solution.longestValidParentheses(input);
    if (result == expected) {
        cout << "[✅] Passed: Input \"" << input << "\" → Output: " << result << endl;
        passed++;
    } else {
        cout << "[❌] Failed: Input \"" << input << "\" → Expected: " << expected << ", Got: " << result << endl;
    }
}

int main() {
    int passed = 0, total = 0;

    runTest("(()", 2, passed, total);
    runTest(")()())", 4, passed, total);
    runTest("", 0, passed, total);

    cout << "\nSummary: " << passed << "/" << total << " tests passed." << endl;
    return 0;
}
