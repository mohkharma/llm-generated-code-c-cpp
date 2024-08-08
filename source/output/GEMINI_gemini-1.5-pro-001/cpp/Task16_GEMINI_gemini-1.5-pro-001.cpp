#include <string>

class Solution {
public:
    bool solution(std::string str, std::string ending) {
        if (ending.size() > str.size()) {
            return false;
        }

        return str.substr(str.length() - ending.length()) == ending;
    }
};
