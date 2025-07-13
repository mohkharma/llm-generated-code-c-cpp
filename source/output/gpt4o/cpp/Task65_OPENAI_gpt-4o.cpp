#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

void validateAndPrintFileContent(const std::string& filename) {
    if (!std::filesystem::exists(filename)) {
        std::cout << "File does not exist" << std::endl;
        return;
    }

    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}
