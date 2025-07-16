#include <iostream>
#include <fstream>
#include <regex>
#include <string>

int main() {
    std::string filename = "/home/kali/CLionProjects/llm-generated-code-cpp/tests/gpt4o/Task99/inputs.txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        std::cout << "Test case result: FAIL" << std::endl;
        return 1;
    }

    std::regex pattern("^\\d.*\\.$");
    std::string line;
    bool matched = false;

    while (std::getline(file, line)) {
        // Trim whitespace, same as Python's strip()
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (std::regex_match(line, pattern)) {
            std::cout << line << std::endl;
            matched = true;
        }
    }

    file.close();

    if (matched) {
        std::cout << "Test case result: PASS" << std::endl;
    } else {
        std::cout << "Test case result: FAIL" << std::endl;
    }

    return 0;
}
