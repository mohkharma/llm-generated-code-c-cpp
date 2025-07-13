#include <iostream>
#include <fstream>
#include <stdexcept>

void copyFile(const std::string& sourcePath, const std::string& destPath) {
    try {
        std::ifstream source(sourcePath, std::ios::binary);
        std::ofstream dest(destPath, std::ios::binary);

        if (!source.is_open() || !dest.is_open()) {
            throw std::runtime_error("Failed to open files.");
        }

        dest << source.rdbuf();

         source.close();
        dest.close();
    } catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << '\n';
    }
}
