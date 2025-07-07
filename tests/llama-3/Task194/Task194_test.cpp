#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>

#include "../../../source/output/llama-3/cpp/Task194_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

using namespace std;

class TestMaster : public Master {
private:
    string secret;
    int guesses;

public:
    TestMaster(const string& s) : secret(s), guesses(0) {}

    // ❌ Remove override
    int guess(const string& word) {
        guesses++;
        if (word.length() != secret.length()) return -1;
        int match = 0;
        for (int i = 0; i < 6; ++i) {
            if (word[i] == secret[i]) match++;
        }
        return match;
    }

    int getGuesses() const {
        return guesses;
    }
};


bool runTest(const string& testName, const string& secret, const vector<string>& words, int allowedGuesses) {
    vector<string> wordlist = words;
    TestMaster master(secret);
    Solution sol;

    // Suppress output if needed
    streambuf* orig_buf = cout.rdbuf();
    stringstream dummy;
    cout.rdbuf(dummy.rdbuf());

    sol.findSecretWord(wordlist, &master);

    cout.rdbuf(orig_buf); // restore output

    bool passed = master.getGuesses() <= allowedGuesses;
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
