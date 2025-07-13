#include <iostream>
#include <regex>

bool validateURL(const std::string& url) {
    const std::regex pattern("^(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]");
    return std::regex_match(url, pattern);
}

int foo(const std::string &url) {

    if (validateURL(url)) {
        return 1;
    } else {
        return 0;
    }
    return 0;
}