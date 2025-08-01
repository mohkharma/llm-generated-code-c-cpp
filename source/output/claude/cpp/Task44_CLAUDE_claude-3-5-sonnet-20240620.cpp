
#include <iostream>
#include <string>
#include <regex>

bool validateInput(const std::string& input) {
    std::regex pattern("^[a-zA-Z0-9\\\\s]+$");
    return std::regex_match(input, pattern);
}

std::string processInput(std::string input) {
    for (char& c : input) {
        c = std::toupper(c);
    }
    return input;
}
