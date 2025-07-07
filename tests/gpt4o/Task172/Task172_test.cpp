#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

// حل الطالب (كما هو)
int distinctAASubstrings(string text) {
    unordered_set<string> distinctSubstrings;
    int n = text.length();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; j += 2) {
            string a = text.substr(i, (j + 1 - i) / 2);
            string b = text.substr(i + (j + 1 - i) / 2, (j + 1 - i) / 2);
            if (a == b) {
                distinctSubstrings.insert(text.substr(i, j - i + 1));
            }
        }
    }

    return distinctSubstrings.size();
}

int main() {
    vector<tuple<string, int, string>> tests = {
        {"abcabcabc", 3, "Test Case 1"},
        {"leetcodeleetcode", 2, "Test Case 2"},
        {"a", 0, "Test Case 3"},
        {"aa", 1, "Test Case 4"},
        {"aaa", 1, "Test Case 5"},
        {"abab", 2, "Test Case 6"},
        {"abcde", 0, "Test Case 7"},
        {"abababab", 4, "Test Case 8"},
        {"abcabcabcabc", 6, "Test Case 9"}
    };

    int passed = 0;
    int total = tests.size();

    for (const auto& [input, expected, caseName] : tests) {
        int actual = distinctAASubstrings(input);
        if (actual == expected) {
            cout << caseName << " Passed ✅" << endl;
            passed++;
        } else {
            cout << caseName << " FAILED ❌: Expected " << expected << ", Got " << actual << endl;
        }
    }

    cout << "\nSummary: " << passed << " / " << total << " tests passed." << endl;

    return 0;
}
