#include <iostream>
#include <string>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <tuple>

class Solution {
public:
    int distinctEchoSubstrings(std::string text) {
        int n = text.length();
        std::unordered_set<std::string> result;

        for (int i = 0; i < n; i++) {
            for (int length = 1; length <= (n - i) / 2; length++) {
                if (text.substr(i, length) == text.substr(i + length, length)) {
                    result.insert(text.substr(i, 2 * length));
                }
            }
        }

        return result.size();
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
        {"abababab", 4, "Test Case 8"},  // اعتمدنا 4 كقيمة صحيحة
        {"abcabcabcabc", 6, "Test Case 9"}
    };

    bool all_passed = true;

    for (const auto& [input, expected, name] : tests) {
        int actual = sol.distinctEchoSubstrings(input);
        if (actual != expected) {
            std::cout << name << " Failed: expected " << expected << ", got " << actual << std::endl;
            all_passed = false;
        }
    }

    if (all_passed) {
        std::cout << "All test cases passed!" << std::endl;
    }

    return 0;
}
