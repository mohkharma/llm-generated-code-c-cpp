#include <iostream>
#include <regex>

int foo(const std::string &user_input) {
    std::regex pattern("^[a-zA-Z0-9_]{3,16}$");

    if (std::regex_match(user_input, pattern)) {
        return 1;
    } else {
        return 0;
    }

}