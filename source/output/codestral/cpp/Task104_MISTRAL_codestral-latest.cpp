#include <iostream>
#include <cstring>

const int BUFFER_SIZE = 10;

char* handleInput(const char* input) {
    static char buffer[BUFFER_SIZE];
    std::strncpy(buffer, input, BUFFER_SIZE - 1);
    buffer[BUFFER_SIZE - 1] = '\0';
    return buffer;
}