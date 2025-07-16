#include <iostream>
#include <fstream>
#include <string>

bool comparePasswords(const std::string& filePath, const std::string& userPassword) {
    std::ifstream file(filePath);
    std::string storedPassword;

    if (file.is_open()) {
        std::getline(file, storedPassword);
        file.close();

        if (userPassword == storedPassword) {
            return true;
        } else {
            return false;
        }
    } else {
        std::cerr << "Error reading the file." << std::endl;
        return false;
    }
}

int main() {
    std::string filePath = "/home/kali/CLionProjects/llm-generated-code-cpp/tests/codestral/Task89/password.txt";
    std::string userPassword;

    std::cout << "Enter your password: ";
    std::getline(std::cin, userPassword);

    if (comparePasswords(filePath, userPassword)) {
        std::cout << "Password is correct." << std::endl;
        std::cout << "Test case 1 result: PASS" << std::endl;
    } else {
        std::cout << "Password is incorrect." << std::endl;
        std::cout << "Test case 1 result: FAIL" << std::endl;
    }

    return 0;
}
