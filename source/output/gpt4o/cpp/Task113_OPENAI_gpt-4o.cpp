#include <iostream>
#include <string>

std::string foo(std::string &inputStr1, std::string &inputStr2) {
    std::string result = inputStr1 + inputStr2;
    return result ;
}