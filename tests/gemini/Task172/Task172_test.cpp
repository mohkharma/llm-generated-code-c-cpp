#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <tuple>

class Solution {
public:
    int distinctEchoSubstrings(std::string text) {
        int n = text.length();
        std::unordered_set<std::string> s;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                std::string sub = text.substr(i, j - i);
                if (sub.length() % 2 == 0 &&
                    sub.substr(0, sub.length() / 2) == sub.substr(sub.length() / 2)) {
                    s.insert(sub);
                }
            }
        }
        return s.size();
    }
};

int main() {
    Solution sol;

    std::vector<std::tuple<std::string, int, std::string>> tests = {
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
        int result = sol.distinctEchoSubstrings(input);
        if (result == expected) {
            std::cout << caseName << " Passed ✅" << std::endl;
            passed++;
        } else {
            std::cout << caseName << " FAILED ❌: Expected " << expected << ", Got " << result << std::endl;
        }
    }

    std::cout << "\nSummary: " << passed << " / " << total << " tests passed." << std::endl;

    return 0;
}
