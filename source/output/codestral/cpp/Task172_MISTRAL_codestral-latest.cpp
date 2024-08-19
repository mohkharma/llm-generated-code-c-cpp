#include <iostream>
#include <string>

bool repeatedSubstringPattern(std::string s) {
    int n = s.length();
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0 && std::string(n / i, s[0]) == std::string(n, s[0]).substr(0, n)) {
            return true;
        }
    }
    return false;
}

int numDistinct(std::string text) {
    int n = text.length();
    int count = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (repeatedSubstringPattern(text.substr(0, i))) {
            count++;
        }
    }
    return count;
}

int main() {
    std::string text = "abcabcabc";
    std::cout << numDistinct(text) << std::endl;
    return 0;
}
