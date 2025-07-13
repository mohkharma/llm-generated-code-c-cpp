#include <iostream>
#include <cstdio>
#include <string>

void deleteFile(const std::string& filePath) {
    if (std::remove(filePath.c_str()) == 0) {
        std::cout << "File '" << filePath << "' has been deleted successfully." << std::endl;
    } else {
        std::perror("Error");
        std::cout << "Unable to delete '" << filePath << "'." << std::endl;
    }
}
