#include <string>   // Include the string header
#include <vector>   // Include the vector header

class Solution {
public:
    std::string shortestPalindrome(std::string s) { // Use std::string
        std::string a = s + "#" + std::string(rbegin(s), rend(s)); // Use std::string
        std::vector<int> k(a.size()); // Use std::vector

        for (int i = 1; i < a.size(); i++) {
            int j = k[i - 1];
            while (j > 0 && a[i] != a[j]) {
                j = k[j - 1];
            }
            k[i] = j + (a[i] == a[j] ? 1 : 0); // Corrected operator precedence
        }

        return std::string(rbegin(s) + k[k.size() - 1], rend(s)) + s; // Use std::string
    }
};
