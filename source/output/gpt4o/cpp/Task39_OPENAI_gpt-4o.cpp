#include <iostream>
#include <cstdlib>
#include <string>

void printFileCrossPlatform(const std::string& filename) {
    std::string command;

#ifdef _WIN32
    command = "type " + filename;
#else
    command = "cat " + filename;
#endif

    if (system(nullptr)) {
        system(command.c_str());
    } else {
        std::cerr << "No command processor available." << std::endl;
    }
}
