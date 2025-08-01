#include <iostream>
#include <string>
#include <cstdlib>

void runCatCommandOnFile(const std::string& filename) {
    std::string command = "cat " + filename;
    std::system(command.c_str());
}
