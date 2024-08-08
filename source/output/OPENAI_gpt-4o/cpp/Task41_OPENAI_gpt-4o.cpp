#include <iostream>
#include <string>

int main() {
    std::string userInput;

    std::cout << "Please enter a string: ";
    std::getline(std::cin, userInput);  // Safely read a line of input from the user

    // Process the input string (e.g., output the length of the input)
    std::cout << "You entered: " << userInput << std::endl;
    std::cout << "Length of the input string: " << userInput.length() << std::endl;

    return 0;
}
