#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "../../../source/output/codestral/cpp/Task194_MISTRAL_codestral-latest.cpp"

using namespace std;

class Master {
private:
    string secret;
    int guesses;

public:
    Master(string s) : secret(std::move(s)), guesses(0) {}

    int guess(const string& word) {
        guesses++;
        if (word.length() != secret.length()) return -1;
        int matches = 0;
        for (size_t i = 0; i < secret.size(); ++i) {
            if (word[i] == secret[i]) matches++;
        }
        return matches;
    }

    int getGuesses() const {
        return guesses;
    }
};

bool runTest(const string& testName, const string& secret, vector<string> words, int allowedGuesses) {
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
