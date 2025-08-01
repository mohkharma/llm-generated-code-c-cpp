#include <iostream>
#include <string>

void readAndPrintInput() {
    std::string input;
    std::getline(std::cin, input);
    // Process the string safely here if needed
    std::cout << input << std::endl;
}