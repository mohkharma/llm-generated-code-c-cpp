#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
using namespace std;

// ---------- Start of Provided Solution (untouched) ----------
#include <unordered_set>

class Solution {
public:
    std::string longestDupSubstring(std::string  s) {
        int left = 0, right = s.length();
        std::string result = "";
        while (left < right) {
            int mid = left + (right - left) / 2;
            std::string candidate = rabinKarp(s, mid);
            if (!candidate.empty()) {
                left = mid + 1;
                result = candidate;
            } else {
                right = mid;
            }
        }
        return result;
    }

private:
    std::string rabinKarp(const std::string& s, int length) {
        long long q = (1LL << 31) - 1;
        long long h = 0;
        for (int i = 0; i < length; i++) {
            h = (h * 26 + s[i] - 'a') % q;
        }

        std::unordered_set<long long> seen;
        seen.insert(h);
        long long aL = 1;
        for (int i = 0; i < length; i++) {
            aL = (aL * 26) % q;
        }

        for (int start = 1; start <= s.length() - length; start++) {
            h = (h * 26 - (s[start - 1] - 'a') * aL % q + q) % q;
            h = (h + s[start + length - 1] - 'a') % q;
            if (seen.count(h)) {
                return s.substr(start, length);
            }
            seen.insert(h);
        }

        return "";
    }
};
// ---------- End of Provided Solution ----------

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
        cout << "All challenging test cases passed!\n";
    }

    return 0;
}
