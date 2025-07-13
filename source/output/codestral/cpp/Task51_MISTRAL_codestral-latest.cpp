#include <iostream>
#include <string>

std::string encryptString(const std::string& inputString, int key) {
    std::string encryptedString;
    for (char c : inputString) {
        if (std::isalpha(c)) {
            int asciiOffset = std::isupper(c) ? 65 : 97;
            encryptedString += static_cast<char>((c - asciiOffset + key) % 26 + asciiOffset);
        } else {
            encryptedString += c;
        }
    }
    return encryptedString;
}

