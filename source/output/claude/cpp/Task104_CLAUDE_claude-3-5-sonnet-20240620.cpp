#include <iostream>
#include <cstring>

#define BUFFER_SIZE 100

void handleInput(const char* input) {
    char buffer[BUFFER_SIZE];
    size_t inputLength = strlen(input);

    if (inputLength < BUFFER_SIZE) {
        strncpy(buffer, input, BUFFER_SIZE - 1);
        buffer[BUFFER_SIZE - 1] = '\0';
        std::cout << "Input stored in buffer: " << buffer << std::endl;
    } else {
        strncpy(buffer, input, BUFFER_SIZE - 1);
        buffer[BUFFER_SIZE - 1] = '\0';
        std::cout << "Input truncated to fit buffer: " << buffer << std::endl;
    }
}