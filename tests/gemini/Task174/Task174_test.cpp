#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        long long base = 26, mod = 1e9 + 7;
        long long hashVal = 0, powBase = 1;
        int best = 0;
        for (int i = n - 1; i >= 0; --i) {
            hashVal = (hashVal * base + (s[i] - 'a')) % mod;
            if (i == 0 || this->isPalindrome(s, 0, i)) {
                best = i + 1;
            }
        }
        return string(s.rbegin(), s.rbegin() + n - best) + s;
    }

private:
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            ++left;
            --right;
        }
        return true;
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
