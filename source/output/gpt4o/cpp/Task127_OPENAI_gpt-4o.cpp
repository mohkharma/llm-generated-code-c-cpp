#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>

void copy_file(const std::string &source_path, const std::string &dest_path) {
    std::ifstream source(source_path, std::ios::binary);
    std::ofstream dest(dest_path, std::ios::binary);

    if (!source.is_open()) {
        throw std::runtime_error("Error: The file at " + source_path + " does not exist.");
    }

    if (!dest.is_open()) {
        throw std::runtime_error("Error: Unable to open destination file.");
    }

    dest << source.rdbuf();
}

