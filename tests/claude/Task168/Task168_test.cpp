// Task168_Test.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>

// الحل كما أعطيت
std::string tweakLetters(const std::string& word, const std::vector<int>& arr) {
    std::string result = word;
    for (size_t i = 0; i < word.length() && i < arr.size(); ++i) {
        result[i] = (result[i] - 'a' + arr[i] + 26) % 26 + 'a';
    }
    return result;
}

// اختبار مطابق لمنطق بايثون تماما
void run_tests() {
    struct TestCase {
        std::string input_word;
        std::vector<int> input_arr;
        std::string expected;
    };

    TestCase tests[] = {
        {"apple", {0, 1, -1, 0, -1}, "aqold"},
        {"many", {0, 0, 0, -1}, "manx"},
        {"rhino", {1, 1, 1, 1, 1}, "sijop"},
        {"abc", {1, 1, 1}, "bcd"},
        {"xyz", {1, 1, 1}, "yza"},
        {"hello", {-1, 0, 1, 0, -1}, "gemln"},
        {"test", {-1, -1, -1, -1}, "sdrs"},
        {"abcd", {1, 2, 3, 4}, "bdfh"},
        {"zzz", {-1, -1, -1}, "yyy"},
        {"world", {0, 1, -1, 2, -2}, "wpqnb"}
    };

    for (int i = 0; i < 10; ++i) {
        std::string output = tweakLetters(tests[i].input_word, tests[i].input_arr);
        assert(output == tests[i].expected && "Test failed!");
    }

    std::cout << "all Task Good\n";
}

int main() {
    run_tests();
    return 0;
}
