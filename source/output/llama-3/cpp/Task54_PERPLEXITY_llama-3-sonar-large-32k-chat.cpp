#include <iostream>
#include <ctime>
#include <cstdlib>

std::string generateOTP() {
    srand(static_cast<unsigned int>(time(0)));
    return std::to_string(rand() % 900000 + 100000);
}

std::string authenticate(std::string username, std::string password, std::string otp) {
    if (username == "admin" && password == "password" && otp == generateOTP()) {
        return "Authentication successful";
    } else {
        return "Authentication failed";
    }
}
