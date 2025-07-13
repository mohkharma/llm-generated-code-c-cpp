#include <iostream>
#include <cstdio>
#include <cstring>

bool validateCommand(const std::string& command) {
    // Simple validation: check if command is not empty
    return !command.empty() && command.find_first_not_of(' ') != std::string::npos;
}
