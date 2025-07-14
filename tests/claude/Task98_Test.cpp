#include <iostream>
#include <string>

int main() {
    std::string userInput;
    std::cout << "Enter a number: ";
    std::getline(std::cin, userInput);

    try {
        int number = std::stoi(userInput);
        std::cout << "Successfully converted to integer: " << number << std::endl;
        std::cout << "Test case result: PASS" << std::endl;
    } catch (const std::invalid_argument&) {
        std::cout << "Invalid input. Please enter a valid integer." << std::endl;
        std::cout << "Test case result: FAIL" << std::endl;
    } catch (const std::out_of_range&) {
        std::cout << "Number out of range for integer conversion." << std::endl;
        std::cout << "Test case result: FAIL" << std::endl;
    }

    return 0;
}
