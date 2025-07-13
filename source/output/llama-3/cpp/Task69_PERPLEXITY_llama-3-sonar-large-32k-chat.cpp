#include <iostream>
#include <fstream>
#include <string>

void deleteFileSimple(const std::string& filePath) {
    if (std::remove(filePath.c_str()) != 0) {
        std::cout << "Failed to delete the file" << std::endl;
    } else {
        std::cout << "File deleted successfully" << std::endl;
    }
}
