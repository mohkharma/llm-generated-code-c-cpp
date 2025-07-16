#include <iostream>
#include <cstdlib>
#include <string>

void displayFileWithSystem(const std::string& filename) {
    std::string command = "cat " + filename;
    std::system(command.c_str());
}
