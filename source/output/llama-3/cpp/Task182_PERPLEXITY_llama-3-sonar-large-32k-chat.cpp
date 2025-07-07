#include <regex>
#include <string>
#include <iostream>

std::string cleanPhoneNumber(const std::string& phoneNumber) {
    std::regex re("[^\\d]");
    std::string cleaned = std::regex_replace(phoneNumber, re, "");
    if (cleaned.size() > 0 && cleaned[0] == '1') {
        cleaned.erase(0, 1);
    }
    return cleaned;
}

