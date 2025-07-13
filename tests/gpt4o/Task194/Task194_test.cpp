#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "../../../source/output/gpt4o/cpp/Task194_OPENAI_gpt-4o.cpp"

using namespace std;

// Global variable from solution file
extern vector<string> words;

bool runTest(const string& testName, const string& secret, const vector<string>& wordList, int allowedGuesses) {
    words = wordList; // update global words list
    Master master(secret);

    // Redirect cout to stringstream to suppress actual output
    streambuf* orig_buf = cout.rdbuf();
    stringstream dummy;
    cout.rdbuf(dummy.rdbuf());

    findSecretWord(words, master, allowedGuesses);

    cout.rdbuf(orig_buf); // restore cout

    bool passed = (master.guess_count <= allowedGuesses);
    cout << "Test: " << testName << " => "
         << (passed ? "✅ Passed" : "❌ Failed")
         << " | Guesses used: " << master.guess_count << "/" << allowedGuesses << endl;
    return passed;
}

int main() {
    int passed = 0, total = 0;

    {
        vector<string> wordList = {"acckzz", "ccbazz", "eiowzz", "abcczz"};
        string secret = "acckzz";
        total++;
        if (runTest("Basic Match Test", secret, wordList, 10)) passed++;
    }

    {
        vector<string> wordList = {"hamada", "khaled"};
        string secret = "hamada";
        total++;
        if (runTest("Two Words Test", secret, wordList, 10)) passed++;
    }

    cout << "\nSummary: " << passed << " / " << total << " tests passed." << endl;
    return 0;
}
