#include <string>
#include <vector>
#include <sstream>

// override by cloude
std::string foo(const std::string &s) {
    std::vector<std::string> strings;
    std::istringstream iss(s);
    std::string word;
    while (iss >> word) {
        strings.push_back(word);
    }
    std::string result;
    for (const auto& str : strings) {
        if (!result.empty()) {
            result += " ";
        }
        result += str;
    }
    return result;
}