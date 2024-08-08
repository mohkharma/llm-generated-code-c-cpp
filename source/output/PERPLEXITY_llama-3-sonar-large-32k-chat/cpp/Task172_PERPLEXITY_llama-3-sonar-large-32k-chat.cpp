#include <string>          // Include the string header
#include <unordered_set>   // Include the unordered_set header
#include <iostream>        // Optional: for debugging or output

class Solution {
public:
    int distinctEchoSubstrings(std::string text) {  // Use std::string
        int n = text.length();                        // Use length() method on std::string
        std::unordered_set<std::string> res;         // Use std::unordered_set

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                std::string s = text.substr(i, j - i); // Use std::string
                if (isPalindrome(s)) {
                    res.insert(s);
                }
            }
        }
        return res.size();
    }

    bool isPalindrome(std::string s) {                // Use std::string
        int i = 0, j = s.length() - 1;               // Use length() method on std::string
        while (i < j) {
            if (s[i] != s[j]) {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }
};
