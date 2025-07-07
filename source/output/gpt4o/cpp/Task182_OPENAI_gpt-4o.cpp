#include <iostream>
#include <vector>
#include <regex>

std::string cleanNumber(std::string number) {
    number = std::regex_replace(number, std::regex("[^0-9]"), "");
    if (number.length() == 11 && number[0] == '1') {
        number = number.substr(1);
    }
    return number;
}

