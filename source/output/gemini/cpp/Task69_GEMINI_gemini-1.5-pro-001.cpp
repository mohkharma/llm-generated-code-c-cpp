#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

void deleteFileWithCheck(const std::string& filePathStr) {
    std::filesystem::path filePath = filePathStr;

    if (!std::filesystem::exists(filePath)) {
        std::cerr << "Error: File '" << filePath << "' not found." << std::endl;
        return;
    }

    try {
        std::filesystem::remove(filePath);
        std::cout << "File '" << filePath << "' deleted successfully." << std::endl;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error deleting file '" << filePath << "': " << e.what() << std::endl;
    }
}
