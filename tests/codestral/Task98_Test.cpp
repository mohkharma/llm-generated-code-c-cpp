#include <iostream>

int main() {
    int userInput;
    std::cout << "Enter a number: ";
    if (std::cin >> userInput) {
        std::cout << "You entered: " << userInput << std::endl;
        std::cout << "Test case result: PASS" << std::endl;
    } else {
        std::cout << "Invalid input. Please enter an integer." << std::endl;
        std::cout << "Test case result: FAIL" << std::endl;
    }
    return 0;
}
