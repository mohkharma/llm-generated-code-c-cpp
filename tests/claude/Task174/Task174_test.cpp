#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cassert>

using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        string rev = s;
        reverse(rev.begin(), rev.end());
        string temp = s + "#" + rev;
        vector<int> lps(temp.length(), 0);

        for (int i = 1; i < temp.length(); i++) {
            int j = lps[i - 1];
            while (j > 0 && temp[i] != temp[j]) {
                j = lps[j - 1];
            }
            if (temp[i] == temp[j]) {
                j++;
            }
            lps[i] = j;
        }

        return rev.substr(0, s.length() - lps.back()) + s;
    }
};

int main() {
    Solution sln;

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
        string result = sln.shortestPalindrome(test.input);
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
