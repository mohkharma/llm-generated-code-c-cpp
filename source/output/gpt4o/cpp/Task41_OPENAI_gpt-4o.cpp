#include <iostream>
#include <string>

void processUserInput() {
    std::string userInput;

    std::cout << "Please enter a string: ";
    std::getline(std::cin, userInput);  // Safely read a line of input from the user

    std::cout << "You entered: " << userInput << std::endl;
    std::cout << "Length of the input string: " << userInput.length() << std::endl;
}
