#include <iostream>
#include <string>
#include <vector>
using namespace std;

// -------- Start of Provided Solution (Unchanged) --------
#include <unordered_map>

long long roll_hash(const string &s, int length) {
    const long long p = 31, m = (1LL << 61) - 1;
    long long hash_value = 0, p_pow = 1;
    for (int i = 0; i < length; ++i) {
        hash_value = (hash_value + (s[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

string search_substring(const string &s, int length) {
    unordered_map<long long, vector<int>> hashes;
    const long long p = 31, m = (1LL << 61) - 1;
    long long curr_hash = roll_hash(s, length);
    long long p_pow = 1;
    for (int i = 1; i < length; ++i) p_pow = (p_pow * p) % m;
    hashes[curr_hash].push_back(0);

    for (int i = 1; i <= s.size() - length; ++i) {
        curr_hash = (curr_hash - (s[i - 1] - 'a' + 1) * p_pow % m + m) % m;
        curr_hash = (curr_hash * p + (s[i + length - 1] - 'a' + 1)) % m;
        if (hashes.count(curr_hash)) {
            for (int start : hashes[curr_hash]) {
                if (s.substr(start, length) == s.substr(i, length)) {
                    return s.substr(start, length);
                }
            }
        }
        hashes[curr_hash].push_back(i);
    }
    return "";
}

string longestDupSubstring(string s) {
    int left = 1, right = s.size() - 1;
    string result;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        string substring = search_substring(s, mid);
        if (!substring.empty()) {
            result = substring;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}
// -------- End of Provided Solution --------

int main() {
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
        string result = longestDupSubstring(testCases[i].input);
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
