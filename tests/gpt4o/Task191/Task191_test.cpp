#include <iostream>
#include <string>

#define main __dummy_main
#include "../../../source/output/gpt4o/cpp/Task191_OPENAI_gpt-4o.cpp"
#undef main

using namespace std;

void runTest(const string& input, int expected, int& passed, int& total) {
    total++;
    int result = longestValidParentheses(input);  // إذا الحل global
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
