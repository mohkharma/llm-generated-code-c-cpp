#include <iostream>
#include <string>

std::string foo(int numStrings, std::string temp) {

    std::string result = "";
    for (int i = 0; i < numStrings; i++) {
        result += temp + " ";
    }
    return result;

}