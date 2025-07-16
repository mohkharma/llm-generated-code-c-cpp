#include <iostream>
#include <string>
#include <cctype>

std::string getUserInput(const std::string& prompt) {
    std::string inputStr;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, inputStr);
        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "Invalid input. Please try again." << std::endl;
        } else {
            return inputStr;
        }
    }
}

void validateInput(const std::string& inputStr) {
    for (char c : inputStr) {
        if (!std::isalpha(c)) {
            throw std::runtime_error("Input should only contain alphabets");
        }
    }
}
