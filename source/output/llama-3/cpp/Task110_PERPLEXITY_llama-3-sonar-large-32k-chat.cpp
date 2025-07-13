#include <iostream>
#include <regex>
#include <string>

bool validateUrl(const std::string& url) {
    std::regex pattern("^(https?|ftp|file)://[-A-Za-z0-9+&@#/%?=~_|!:,.;]*[-A-Za-z0-9+&@#/%=~_|]");
    return std::regex_match(url, pattern);
}

int foo(const std::string& url) {

    if (validateUrl(url)) {
        return 1;
    } else {
        return 0;
    }
}