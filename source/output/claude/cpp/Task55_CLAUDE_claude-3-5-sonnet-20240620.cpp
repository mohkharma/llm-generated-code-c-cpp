
#include <iostream>
#include <regex>
#include <string>

bool validateEmail(const std::string& email) {
    const std::regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\\\.[a-zA-Z]{2,}$");
    return std::regex_match(email, pattern);
}
