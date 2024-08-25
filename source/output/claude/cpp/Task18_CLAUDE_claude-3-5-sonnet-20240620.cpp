
#include <iostream>
#include <vector>
#include <string>

int convertBinaryArrayToInt(const std::vector<int>& binary) {
    std::string binaryString;
    for (int digit : binary) {
        binaryString += std::to_string(digit);
    }
    return std::stoi(binaryString, nullptr, 2);
}

