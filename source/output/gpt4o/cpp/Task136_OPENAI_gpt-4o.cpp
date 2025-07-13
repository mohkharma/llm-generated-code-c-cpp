#include <iostream>
#include <string>

bool authenticate(const std::string& username, const std::string& password) {
    std::string storedUsername = "user";
    std::string storedPassword = "pass";
    return username == storedUsername && password == storedPassword;
}

