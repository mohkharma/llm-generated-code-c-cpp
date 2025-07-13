
#include <iostream>
#include <string>
#include <regex>

bool isValidURL(const std::string& url) {
    const std::regex urlRegex(R"(^(https?|ftp)://[^\\s/$.?#].[^\\s]*$)", std::regex::icase);
    return std::regex_match(url, urlRegex);
}

int foo(const std::string &url) {

    while (true) {
        if (url == "quit") {
            break;
        }
        if (isValidURL(url)) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
