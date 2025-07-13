
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

std::string encrypt(const std::string& data) {
    std::string result = data;
    for (char& c : result) {
        c = c + 1;
    }
    return result;
}

std::string decrypt(const std::string& encodedData) {
    std::string result = encodedData;
    for (char& c : result) {
        c = c - 1;
    }
    return result;
}
