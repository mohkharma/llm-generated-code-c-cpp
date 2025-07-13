#include <iostream>
#include <filesystem>
#include <string>

void safelyDeleteFile(const std::string& filePathStr) {
    std::filesystem::path file_path = filePathStr;

    try {
        if (std::filesystem::remove(file_path)) {
            std::cout << file_path << " deleted successfully." << std::endl;
        } else {
            std::cerr << file_path << " does not exist." << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
