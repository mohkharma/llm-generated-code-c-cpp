#include <iostream>
#include <regex>

bool validateURL(const std::string &url) {
    const std::regex pattern("(http|https|ftp)://([^\\s/$.?#].[^\\s]*)");
    return std::regex_match(url, pattern);
}

int foo(const std::string &userURL) {

    if (validateURL(userURL)) {
           return 1;
    } else {
        return 0;
    }

    return 0;
}