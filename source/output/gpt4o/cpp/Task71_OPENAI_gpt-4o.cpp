#include <iostream>
#include <string>

void convertStringToInt(const std::string& inputStr) {
    try {
        int convertedInt = std::stoi(inputStr);
        std::cout << "Converted integer: " << convertedInt << std::endl;
    } catch (const std::invalid_argument&) {
        std::cout << "Invalid input: Not a valid integer." << std::endl;
    }
}
