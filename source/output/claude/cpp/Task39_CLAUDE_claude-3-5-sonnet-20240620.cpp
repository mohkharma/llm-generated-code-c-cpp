#include <iostream>
#include <cstdlib>
#include <string>

void printFileUsingSystemCat(const std::string& filename) {
    std::string command = "cat " + filename;
    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "Error executing command" << std::endl;
    }
}
