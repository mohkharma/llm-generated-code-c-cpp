#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return "File not found.";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
