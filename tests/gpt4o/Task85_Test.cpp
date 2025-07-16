#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>

// كودك كما هو تماماً
std::string generateRandomString(int length) {
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string result;
    std::srand(std::time(0));

    for (int i = 0; i < length; ++i) {
        result += characters[std::rand() % characters.length()];
    }
    return result;
}

// دالة تحقق التيست كيس
bool is_valid_random_string(const std::string& s, int expected_length) {
    if ((int)s.length() != expected_length)
        return false;
    for (char c : s) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            return false;
        }
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
