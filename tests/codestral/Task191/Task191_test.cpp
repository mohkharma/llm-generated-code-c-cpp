#include <iostream>
#include <sstream>
#include <string>
#include "../../../source/output/codestral/cpp/Task191_MISTRAL_codestral-latest.cpp"

using namespace std;

void runTest(const string& input, int expected, int& passed, int& total) {
    total++;
    int result = longestValidParentheses(input);
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
