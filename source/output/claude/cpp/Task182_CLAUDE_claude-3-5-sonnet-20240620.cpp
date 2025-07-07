
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

std::string clean_phone_number(const std::string& phone) {
    std::string digits;
    std::copy_if(phone.begin(), phone.end(), std::back_inserter(digits), ::isdigit);
    
    if (digits.length() == 11 && digits[0] == '1') {
        return digits.substr(1);
    } else if (digits.length() == 10) {
        return digits;
    } else {
        throw std::invalid_argument("Invalid phone number");
    }
}

