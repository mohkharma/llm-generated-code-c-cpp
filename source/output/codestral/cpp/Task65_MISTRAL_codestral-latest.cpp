#include <iostream>
#include <fstream>
#include <string>

void readFileAndPrintLines(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cout << "Error: Unable to open the file." << std::endl;
    }
}
