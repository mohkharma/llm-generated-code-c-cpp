#include <iostream>
#include <filesystem>
#include <string>

void deleteFileIfExists(const std::string& filePath) {
    std::filesystem::path path(filePath);

    if (std::filesystem::exists(path)) {
        if (std::filesystem::remove(path)) {
            std::cout << "File " << filePath << " has been deleted." << std::endl;
        } else {
            std::cout << "Failed to delete the file." << std::endl;
        }
    } else {
        std::cout << "File " << filePath << " does not exist." << std::endl;
    }
}
