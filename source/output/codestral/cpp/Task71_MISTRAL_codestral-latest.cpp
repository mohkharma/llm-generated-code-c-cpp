#include <iostream>
#include <cstdlib>
#include <string>

void parseAndPrintInteger(const std::string& input) {
    char* end;
    long num = std::strtol(input.c_str(), &end, 10);

    if (*end != '\0') {
        std::cout << "Invalid input. Please enter an integer." << std::endl;
    } else {
        std::cout << num << std::endl;
    }
}
