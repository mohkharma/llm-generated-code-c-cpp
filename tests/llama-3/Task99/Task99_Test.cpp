#include <iostream>
#include <fstream>
#include <regex>
#include <string>

int main() {
    std::ifstream file("/home/kali/CLionProjects/llm-generated-code-cpp/tests/llama-3/Task99/inputs.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open file: input.txt" << std::endl;
        std::cout << "Test case result: FAIL" << std::endl;
        return 1;
    }

    std::string line;
    std::regex pattern("^\\d+.*\\.$");
    bool matched = false;

    while (std::getline(file, line)) {
        // Trim leading and trailing whitespace to match Python's strip
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
