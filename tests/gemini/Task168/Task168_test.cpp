#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// الدالة التي زودتنا بها، بدون تعديل
std::string tweakLetters(std::string txt, std::vector<int> arr) {
    std::string res = "";
    for (size_t i = 0; i < txt.length(); i++) {
        if (arr[i] == 1) {
            res += char(txt[i] + 1);
        } else if (arr[i] == -1) {
            res += char(txt[i] - 1);
        } else {
            res += txt[i];
        }
    }
    return res;
}

// دالة اختبار تطابق اختبارات بايثون
void run_tests() {
    struct TestCase {
        std::string input_word;
        std::vector<int> tweaks;
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

    bool all_passed = true;
    for (int i = 0; i < 10; ++i) {
        std::string output = tweakLetters(tests[i].input_word, tests[i].tweaks);
        if (output != tests[i].expected) {
            std::cerr << "Test case " << (i+1) << " FAILED.\n";
            std::cerr << "Input word: " << tests[i].input_word << "\n";
            std::cerr << "Tweaks: ";
            for (int v : tests[i].tweaks) std::cerr << v << " ";
            std::cerr << "\nExpected: " << tests[i].expected << "\nGot:      " << output << "\n\n";
            all_passed = false;
        }
    }
    if (all_passed) {
        std::cout << "all Task Good\n";
    }
}

int main() {
    run_tests();
    return 0;
}
