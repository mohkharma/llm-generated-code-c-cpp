#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./file_reader <file_path>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[1]);
    if (!file) {
        std::cout << "File not found" << std::endl;
        return 1;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    return 0;
}