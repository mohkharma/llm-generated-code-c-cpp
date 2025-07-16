#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

// كودك كما هو
std::string generateRandomString(int length) {
    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string str;
    srand(time(0));
    for (int i = 0; i < length; i++) {
        str += chars[rand() % chars.length()];
    }
    return str;
}

// دالة تحقق التيست كيس
bool is_valid_random_string(const std::string& s, int expected_length) {
    if ((int)s.length() != expected_length) return false;
    for (char c : s) {
        if (!std::isalpha(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

int main() {
    int length = 10;
    std::string random_str = generateRandomString(length);

    std::cout << "Generated random string: " << random_str << std::endl;

    if (is_valid_random_string(random_str, length)) {
        std::cout << "Test case 1 result: PASS" << std::endl;
    } else {
        std::cout << "Test case 1 result: FAIL" << std::endl;
    }

    return 0;
}

