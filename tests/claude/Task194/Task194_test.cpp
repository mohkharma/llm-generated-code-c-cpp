#include <iostream>
#include <vector>
#include <string>

#include "../../../source/output/claude/cpp/Task194_CLAUDE_claude-3-5-sonnet-20240620.cpp"

using namespace std;

bool runTest(string testName, const string& secret, vector<string> words, int allowedGuesses) {
    Master master(secret);
    Solution sol;
    sol.findSecretWord(words, master);
    bool passed = (master.getGuesses() <= allowedGuesses);
    cout << "Test: " << testName << " => "
         << (passed ? "✅ Passed" : "❌ Failed")
         << " | Guesses used: " << master.getGuesses() << "/" << allowedGuesses << endl;
    return passed;
}

int main() {
    int passed = 0, total = 0;

    {
        string secret = "acckzz";
        vector<string> words = {"acckzz", "ccbazz", "eiowzz", "abcczz"};
        total++;
        if (runTest("Basic Match Test", secret, words, 10)) passed++;
    }

    {
        string secret = "hamada";
        vector<string> words = {"hamada", "khaled"};
        total++;
        if (runTest("Two Words Test", secret, words, 10)) passed++;
    }

    cout << "\nSummary: " << passed << " / " << total << " tests passed." << endl;
    return 0;
}
