#include <iostream>
#include <cstdlib>
#include <ctime>

int generateOTP() {
    return 100000 + std::rand() % 900000;
}

bool verifyOTP(int userOTP, int actualOTP) {
    return userOTP == actualOTP;
}

