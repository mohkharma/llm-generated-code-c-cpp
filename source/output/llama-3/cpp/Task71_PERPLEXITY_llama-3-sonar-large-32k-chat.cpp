#include <iostream>
#include <string>

void printIntegerFromString(const std::string& input) {
    try {
        int num = std::stoi(input);
        std::cout << "The integer value is: " << num << std::endl;
    } catch (const std::invalid_argument&) {
        std::cout << "Invalid input. Please enter a valid integer." << std::endl;
    } catch (const std::out_of_range&) {
        std::cout << "Invalid input. Please enter a valid integer." << std::endl;
    }
}
