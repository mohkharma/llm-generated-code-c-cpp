#include <iostream>
#include <fstream>
#include <regex>
#include <string>

int main() {
    std::ifstream file("/home/kali/CLionProjects/llm-generated-code-cpp/tests/claude/Task99/inputs.txt");  // Use the same filename as Python code
    std::string line;
    // Pattern from Python: r'^\d+.*\.$' - in C++ string, backslash must be escaped once
    std::regex pattern("^\\d+.*\\.$");

    if (!file.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        std::cout << "Test case result: FAIL" << std::endl;
        return 1;
    }

    bool foundMatch = false;
    while (std::getline(file, line)) {
        // trim whitespace from line like Python strip()
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
