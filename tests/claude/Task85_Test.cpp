#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <cctype>

// كودك كما هو تماماً (بدون تعديل)
std::string generate_random_string(int length) {
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result;
    result.reserve(length);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<> distribution(0, characters.length() - 1);

    for (int i = 0; i < length; ++i) {
        result += characters[distribution(generator)];
    }

    return result;
}

// تحقق التيست كيس
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
    int test_length = 10;
    std::string random_str = generate_random_string(test_length);

    std::cout << "Generated random string: " << random_str << std::endl;

    if (is_valid_random_string(random_str, test_length)) {
        std::cout << "Test case 1 result: PASS" << std::endl;
    } else {
        std::cout << "Test case 1 result: FAIL" << std::endl;
    }

    return 0;
}
