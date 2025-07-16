#include <iostream>
#include <string>

void printUserInput() {
    std::string userInput;
    std::cout << "Enter a string: ";
    std::getline(std::cin, userInput);
    std::cout << "You entered: " << userInput << std::endl;
}
