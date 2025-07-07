#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "../../../source/output/gemini/cpp/Task194_GEMINI_gemini-1.5-pro-001.cpp"

using namespace std;

bool runTest(const string& testName, const string& secret, const vector<string>& words, int allowedGuesses) {
    Master master(secret);
    Solution solution;

    // Suppress output
    streambuf* orig = cout.rdbuf();
    stringstream dummy;
    cout.rdbuf(dummy.rdbuf());

    vector<string> wordlist = words; // Copy to avoid side effects
    solution.findSecretWord(wordlist, master);

    cout.rdbuf(orig); // Restore output

    bool passed = (master.getGuesses() <= allowedGuesses);
    cout << "Test: " << testName << " => "
         << (passed ? "✅ Passed" : "❌ Failed")
         << " | Guesses used: " << master.getGuesses() << "/" << allowedGuesses << endl;

    return passed;
}

int main() {
    int passed = 0, total = 0;

    {
        vector<string> words = {"acckzz", "ccbazz", "eiowzz", "abcczz"};
        string secret = "acckzz";
        total++;
        if (runTest("Basic Match Test", secret, words, 10)) passed++;
    }

    {
        vector<string> words = {"hamada", "khaled"};
        string secret = "hamada";
        total++;
        if (runTest("Two Words Test", secret, words, 10)) passed++;
    }

    cout << "\nSummary: " << passed << " / " << total << " tests passed." << endl;
    return 0;
}
