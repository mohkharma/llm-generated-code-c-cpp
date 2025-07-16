#include <iostream>
#include <fstream>
#include <regex>
#include <string>

int main() {
    std::ifstream file("/home/kali/CLionProjects/llm-generated-code-cpp/tests/codestral/Task99/inputs.txt"); // Use same filename as Python code
    if (!file.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        std::cout << "Test case result: FAIL" << std::endl;
        return 1;
    }

    std::string line;
    std::regex pattern("^\\d+.*\\.$"); // Strict match: line starts with digits and ends with dot
    bool foundMatch = false;

    while (std::getline(file, line)) {
        // Trim leading and trailing whitespace to mimic Python strip()
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (std::regex_match(line, pattern)) {
            std::cout << line << std::endl;
            foundMatch = true;
        }
    }
    file.close();

    if (foundMatch) {
        std::cout << "Test case result: PASS" << std::endl;
    } else {
        std::cout << "Test case result: FAIL" << std::endl;
    }

    return 0;
}
