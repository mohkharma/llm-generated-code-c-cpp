#include <iostream>
#include <string>
#include <random>
#include <chrono>

// Note: Sending emails from C++ requires external libraries. 
//       This example focuses on OTP generation and verification.

std::string generateOTP(int length = 6) {
    std::string digits = "0123456789";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, digits.size() - 1);

    std::string otp;
    for (int i = 0; i < length; ++i) {
        otp += digits[distribution(generator)];
    }
    return otp;
}
