#include <iostream>
#include <algorithm>

bool XO(const std::string &str) {
    std::string s = str;
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    int xCount = std::count(s.begin(), s.end(), 'x');
    int oCount = std::count(s.begin(), s.end(), 'o');
    return xCount == oCount;
}

