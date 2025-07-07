#include <iostream>
#include <string>
#include <vector>
using namespace std;

// -------- Start of Given Solution (Unchanged) --------
#include <cmath>
#include <unordered_set>

class Solution {
public:
    std::string longestDupSubstring(std::string s) {
        int n = s.length();
        return check(s, 1, n);
    }
private:
    std::string check(std::string s, int left, int right) {
        if (left > right) {
            return "";
        }
        int mid = left + (right - left) / 2;
        std::string substring = rabinKarp(s, mid);
        if (!substring.empty()) {
            return substring;
        } else {
            std::string leftResult = check(s, left, mid - 1);
            std::string rightResult = check(s, mid + 1, right);
            return leftResult.length() >= rightResult.length() ? leftResult : rightResult;
        }
    }

    std::string rabinKarp(std::string s, int length) {
        if (length == 0) {
            return "";
        }
        int n = s.length();
        std::unordered_set<long long> seen;
        long long modulus = (long long) std::pow(2, 32);
        long long a = 26;
        long long hash = 0;
        long long power = 1;
        for (int i = 0; i < length; i++) {
            hash = (hash * a + (s[i] - 'a')) % modulus;
            power = (power * a) % modulus;
        }
        seen.insert(hash);
        for (int i = 1; i <= n - length; i++) {
            hash = (hash * a - (s[i - 1] - 'a') * power % modulus + modulus) % modulus;
            hash = (hash + (s[i + length - 1] - 'a')) % modulus;
            if (seen.find(hash) != seen.end()) {
                return s.substr(i, length);
            }
            seen.insert(hash);
        }
        return "";
    }
};
// -------- End of Given Solution --------

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
        const string& input = testCases[i].input;
        const string& expected = testCases[i].expected;
        string result = sol.longestDupSubstring(input);
        if (result != expected) {
            cout << "Test Case " << (i + 1) << " Failed!\n";
            cout << "  Input:    " << input << "\n";
            cout << "  Expected: " << expected << "\n";
            cout << "  Got:      " << result << "\n";
            allPassed = false;
        }
    }

    if (allPassed) {
        cout << "All challenging test cases passed!" << endl;
    }

    return 0;
}
