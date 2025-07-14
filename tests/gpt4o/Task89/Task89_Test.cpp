#include <iostream>
#include <fstream>
#include <string>

bool checkPassword(const std::string& inputPassword) {
    std::ifstream file("/home/kali/CLionProjects/llm-generated-code-cpp/tests/gpt4o/Task89/password.txt");
    if (!file.is_open()) return false;

    std::string storedPassword;
    std::getline(file, storedPassword);
    file.close();

    if (storedPassword.length() != inputPassword.length()) return false;

    for (size_t i = 0; i < storedPassword.length(); ++i) {
        if (storedPassword[i] != inputPassword[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    std::string password = "correctpassword";
    std::ofstream file("password.txt");
    file << password;
    file.close();

    std::string userInput;
    std::cout << "Enter your password: ";
    std::cin >> userInput;

    if (checkPassword(userInput)) {
        std::cout << "Password is correct" << std::endl;
        std::cout << "Test case 1 result: PASS" << std::endl;
    } else {
        std::cout << "Password is incorrect" << std::endl;
        std::cout << "Test case 1 result: FAIL" << std::endl;
    }

    return 0;
}
