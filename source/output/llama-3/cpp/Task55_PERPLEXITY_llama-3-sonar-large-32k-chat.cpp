#include <iostream>
#include <regex>

bool validateEmail(const std::string& email) {
    std::regex pattern("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$");
    return std::regex_match(email, pattern);
}

