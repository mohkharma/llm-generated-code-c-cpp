#include <cstring>
#include <iostream>

// Function to handle user input into a fixed-size buffer in C++
int handleUserInputCPP(char* buffer, int bufferSize) {
    std::cin.getline(buffer, bufferSize);
    return std::strlen(buffer);
}

// int main() {
//     char buffer[100];
//     int length;
//
//     // Example usage:
//     length = handleUserInputCPP(buffer, sizeof(buffer));
//     std::cout << "Input in C++: " << buffer << std::endl;
//
//     length = handleUserInputC(buffer, sizeof(buffer));
//     printf("Input in C: %s\n", buffer);
//
//     return 0;
// }