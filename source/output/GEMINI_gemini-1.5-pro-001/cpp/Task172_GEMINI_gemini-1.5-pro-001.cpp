#include <string>
#include <unordered_set>

class Solution {
public:
    int distinctEchoSubstrings(std::string text) {
        int n = text.length();
        std::unordered_set<std::string> s;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                std::string sub = text.substr(i, j - i);
                if (sub.length() % 2 == 0 && sub.substr(0, sub.length() / 2) == sub.substr(sub.length() / 2)) {
                    s.insert(sub);
                }
            }
        }
        return s.size();
    }
};
