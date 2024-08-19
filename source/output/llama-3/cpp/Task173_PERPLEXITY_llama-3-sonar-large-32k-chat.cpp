#include <string>  // Include the string header
#include <iostream> // Optional: for debugging or output

class Solution {
public:
    std::string longestDupSubstring(std::string s) { // Use std::string
        int n = s.size();
        std::string longest = ""; // Use std::string
        for (int len = n / 2; len >= 1; len--) {
            for (int i = 0; i <= n - len; i++) {
                std::string substr = s.substr(i, len); // Use std::string
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
