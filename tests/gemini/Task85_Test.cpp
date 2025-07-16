#include <iostream>
#include <random>
#include <cctype>

// كودك كما هو تماماً
std::string generateRandomString(int length) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<char> distribution('a', 'z');

    std::string randomString;
    for (int i = 0; i < length; ++i) {
        char randomChar = distribution(generator);
        randomString += (i % 2 == 0) ? randomChar : toupper(randomChar);
    }

    return randomString;
}

// تحقق التيست كيس من البايثون
bool is_valid_random_string(const std::string& s, int expected_length) {
    if ((int)s.size() != expected_length) return false;
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
