#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("/home/kali/CLionProjects/llm-generated-code-cpp/tests/llama-3/Task89/password.txt");
    if (!file.is_open()) {
        std::cout << "Password file not found." << std::endl;
        std::cout << "Test case 1 result: FAIL" << std::endl;
        return 1;
    }

    std::string storedPassword;
    std::getline(file, storedPassword);
    file.close();

    std::string userPassword;
    std::cout << "Enter your password: ";
    std::getline(std::cin, userPassword);

    if (storedPassword.length() != userPassword.length()) {
        std::cout << "Password does not match" << std::endl;
        std::cout << "Test case 1 result: FAIL" << std::endl;
    } else {
        bool match = true;
        for (int i = 0; i < storedPassword.length(); i++) {
            if (storedPassword[i] != userPassword[i]) {
                match = false;
                break;
            }
        }
        if (match) {
            std::cout << "Password matches" << std::endl;
            std::cout << "Test case 1 result: PASS" << std::endl;
        } else {
            std::cout << "Password does not match" << std::endl;
            std::cout << "Test case 1 result: FAIL" << std::endl;
        }
    }
    return 0;
}
