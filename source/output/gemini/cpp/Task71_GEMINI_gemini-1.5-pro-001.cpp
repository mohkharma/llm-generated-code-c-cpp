#include <iostream>
#include <string>

void convertToInteger(const std::string& userInput) {
    try {
        int convertedInteger = std::stoi(userInput);
        std::cout << "Successfully converted '" << userInput << "' to integer: " << convertedInteger << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Unable to convert '" << userInput << "' to an integer." << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Unable to convert '" << userInput << "' to an integer. Value out of range." << std::endl;
    }
}
