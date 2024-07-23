
#include <iostream>
#include <string>

const int BUFFER_SIZE = 100;

int main() {
    std::string buffer;
    std::string userInput;

    while (true) {
        std::cout << "Enter text (or 'q' to quit): ";
        std::getline(std::cin, userInput);

        if (userInput == "q" || userInput == "Q") {
            break;
        }

        if (buffer.length() + userInput.length() <= BUFFER_SIZE) {
            buffer += userInput;
            std::cout << "Buffer content: " << buffer << std::endl;
        } else {
            std::cout << "Error: Buffer overflow. Cannot add more than " << BUFFER_SIZE << " characters." << std::endl;
        }
    }

    std::cout << "Final buffer content: " << buffer << std::endl;
    return 0;
}
