#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// دالة الحل الجديدة كما زودتني بها
string shortestPalindrome(string s) {
    int i = 0;
    for (int j = s.length() - 1; j >= 0; j--) {
        if (s[i] == s[j]) {
            i++;
        }
    }
    if (i == s.length()) {
        return s;
    }
    string suffix = s.substr(i);
    string prefix = suffix;
    reverse(prefix.begin(), prefix.end());
    return prefix + shortestPalindrome(s.substr(0, i)) + suffix;
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

    for (const auto& test : tests) {
        string result = shortestPalindrome(test.input);
        if (result != test.expected) {
            cout << test.name << " Failed!\n";
            cout << "  Input:    " << test.input << "\n";
            cout << "  Expected: " << test.expected << "\n";
            cout << "  Got:      " << result << "\n";
            allPassed = false;
        }
    }

    if (allPassed) {
        cout << "All test cases passed!" << endl;
    }

    return 0;
}
