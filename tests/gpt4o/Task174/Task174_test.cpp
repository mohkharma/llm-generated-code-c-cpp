#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// الحل الأخير كما زودتني به
string shortestPalindrome(string s) {
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    for (int i = 0; i <= s.length(); i++) {
        if (s.compare(0, s.length() - i, rev_s, i, s.length() - i) == 0) {
            return rev_s.substr(0, i) + s;
        }
    }
    return "";
}

int main() {
    struct TestCase {
        string input;
        string expected;
        string name;
    };

    vector<TestCase> tests = {
        {"racecar", "racecar", "Test Case 1"},
        {"aacecaaa", "aaacecaaa", "Test Case 2"},
        {"abcd", "dcbabcd", "Test Case 3"},
        {"", "", "Test Case 4"},
        {"a", "a", "Test Case 5"},
        {"aaaaaaaa", "aaaaaaaa", "Test Case 6"},
        {"abcda", "adcbaabcda", "Test Case 7"},
        {"ababababab", "bababababab", "Test Case 8"},
        {"xyz", "zyxyz", "Test Case 9"},
        {"abbaac", "caabbaac", "Test Case 10"}
    };

    bool allPassed = true;
    int passedCount = 0;

    for (const auto& test : tests) {
        string result = shortestPalindrome(test.input);
        if (result != test.expected) {
            cout << test.name << " Failed!\n";
            cout << "  Input:    " << test.input << "\n";
            cout << "  Expected: " << test.expected << "\n";
            cout << "  Got:      " << result << "\n";
            allPassed = false;
        } else {
            passedCount++;
        }
    }

    if (allPassed) {
        cout << "All test cases passed!" << endl;
    } else {
        cout << passedCount << " / " << tests.size() << " test cases passed." << endl;
    }

    return 0;
}
