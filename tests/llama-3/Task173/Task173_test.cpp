#include <iostream>
#include <string>
#include <vector>
using namespace std;

// -------- Start of Your Solution --------
class Solution {
public:
    std::string longestDupSubstring(std::string s) {
        int n = s.size();
        std::string longest = "";
        for (int len = n / 2; len >= 1; len--) {
            for (int i = 0; i <= n - len; i++) {
                std::string substr = s.substr(i, len);
                size_t first = s.find(substr);
                size_t last = s.rfind(substr);
                if (first != last && substr.size() > longest.size()) {
                    longest = substr;
                }
            }
        }
        return longest;
    }
};
// -------- End of Your Solution --------

int main() {
    Solution sol;

    struct TestCase {
        string input;
        string expected;
    };

    vector<TestCase> testCases = {
        {"abcabcabcd", "abcabc"},
        {"abababcababab", "ababab"},
        {"abacabadabacaba", "abacaba"},
        {"abcdefgabcdefgabcdefg", "abcdefgabcdefg"},
        {"aabbaabbaaccddcc", "aabbaa"},
        {"abcdabcdeabcdabcdeabcd", "abcdabcdeabcd"},
        {"abcdefghijklmnoabcdefghijklmno", "abcdefghijklmno"},
        {"xyzxyzxyzxyzx", "xyzxyzxyzx"},
        {"abcdefgh12345678abcdefgh", "abcdefgh"},
        {"abcxabcyabczabcdabc", "abc"}
    };

    bool allPassed = true;

    for (size_t i = 0; i < testCases.size(); ++i) {
        string result = sol.longestDupSubstring(testCases[i].input);
        if (result != testCases[i].expected) {
            cout << "Test Case " << (i + 1) << " Failed!\n";
            cout << "  Input:    " << testCases[i].input << "\n";
            cout << "  Expected: " << testCases[i].expected << "\n";
            cout << "  Got:      " << result << "\n";
            allPassed = false;
        }
    }

    if (allPassed) {
        cout << "All challenging test cases passed!" << endl;
    }

    return 0;
}
