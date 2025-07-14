#include <iostream>
#include <fstream>
#include <string>

bool checkPassword(const std::string& storedPassword, const std::string& enteredPassword) {
    if (storedPassword.length() != enteredPassword.length()) {
        return false;
    }
    for (size_t i = 0; i < storedPassword.length(); i++) {
        if (storedPassword[i] != enteredPassword[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    std::string storedPassword;
    std::ifstream file("/home/kali/CLionProjects/llm-generated-code-cpp/tests/claude/Task89/password.txt");
    if (file.is_open()) {
        std::getline(file, storedPassword);
        file.close();
    } else {
        std::cout << "Password file not found." << std::endl;
        std::cout << "Test case 1 result: FAIL" << std::endl;
        return 1;
    }

    std::string enteredPassword;
    std::cout << "Enter your password: ";
    std::getline(std::cin, enteredPassword);

    if (checkPassword(storedPassword, enteredPassword)) {
        std::cout << "Password correct!" << std::endl;
        std::cout << "Test case 1 result: PASS" << std::endl;
    } else {
        std::cout << "Password incorrect." << std::endl;
        std::cout << "Test case 1 result: FAIL" << std::endl;
    }

    return 0;
}
