#include <iostream>
#include <string>
#include <cctype>

int checkPasswordStrength(const std::string& password) {

    bool hasLower = false, hasUpper = false, hasDigit = false;

    if (password.length() >= 8) {
        for (char c : password) {
            if (islower(c)) hasLower = true;
            if (isupper(c)) hasUpper = true;
            if (isdigit(c)) hasDigit = true;
        }
    }

    if (hasLower && hasUpper && hasDigit && password.length() >= 8) {
        return 1;
    } else {
        return 0;
    }

}