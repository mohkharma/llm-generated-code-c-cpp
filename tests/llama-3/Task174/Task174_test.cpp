#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        string a = s + "#" + string(rbegin(s), rend(s));
        vector<int> k(a.size());

        for (int i = 1; i < a.size(); i++) {
            int j = k[i - 1];
            while (j > 0 && a[i] != a[j]) {
                j = k[j - 1];
            }
            k[i] = j + (a[i] == a[j] ? 1 : 0);
        }

        return string(rbegin(s) + k.back(), rend(s)) + s;
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
    int passedCount = 0;

    for (const auto& test : tests) {
        string result = sln.shortestPalindrome(test.input);
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
