#include <iostream>
#include <regex>
#include <string>
// BY CLAUDE
bool validateEmail(const std::string& email) {
    std::regex email_pattern("^[\\w\\.-]+@[\\w\\.-]+\\.\\w+$");
    return std::regex_match(email, email_pattern);
}

bool validatePhoneNumber(const std::string& phone) {
    std::regex phone_pattern("^\\(?([0-9]{3})\\)?[-. ]?([0-9]{3})[-. ]?([0-9]{4})$");
    return std::regex_match(phone, phone_pattern);
}

bool validatePassword(const std::string& password) {
    std::regex password_pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$");
    return std::regex_match(password, password_pattern);
}

// int main() {
//     std::string input;
//
//     std::cout << "Enter your email: ";
//     std::getline(std::cin, input);
//     std::cout << (validateEmail(input) ? "Valid email" : "Invalid email") << std::endl;
//
//     std::cout << "Enter your phone number: ";
//     std::getline(std::cin, input);
//     std::cout << (validatePhoneNumber(input) ? "Valid phone number" : "Invalid phone number") << std::endl;
//
//     std::cout << "Enter your password: ";
//     std::getline(std::cin, input);
//     std::cout << (validatePassword(input) ? "Valid password" : "Invalid password") << std::endl;
//
//     return 0;
// }