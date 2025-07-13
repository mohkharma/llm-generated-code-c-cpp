#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

std::string generateToken(int length) {
    std::string lettersAndDigits = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    std::string token;
    for (int i = 0; i < length; i++) {
        token += lettersAndDigits[rand() % lettersAndDigits.length()];
    }
    return token;
}

