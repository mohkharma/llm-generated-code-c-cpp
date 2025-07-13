#include <iostream>
#include <fstream>
#include <string>

void readFileLines(const std::string& filePath) {
  std::ifstream file(filePath);

  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::cout << line << std::endl;
    }
    file.close();
  } else {
    std::cerr << "Error: Unable to open file: " << filePath << std::endl;
  }
}
