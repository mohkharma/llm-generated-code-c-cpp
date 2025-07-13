#include <iostream>
#include <string>

std::string encrypt(const std::string& text, int shift) {
    std::string result;

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += (char) ((c - base + shift) % 26 + base);
        } else {
            result += c;
        }
    }

    return result;
}
