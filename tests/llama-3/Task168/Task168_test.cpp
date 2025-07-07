#include <iostream>
#include <string>
#include <cassert>

// دالتك كما هي (بدون تعديل)
std::string tweakLetters(std::string s, int tweaks[]) {
    std::string result = "";
    for (int i = 0; i < (int)s.length(); i++) {
        char c = s[i] + tweaks[i];
        result += c;
    }
    return result;
}

void run_tests() {
    struct TestCase {
        std::string input_word;
        int tweaks[5];  // أقصى طول في الأمثلة هو 5، ممكن تزيد إذا احتجت
        int tweaks_len;
        std::string expected;
    };

    TestCase tests[] = {
        {"apple", {0, 1, -1, 0, -1}, 5, "aqold"},
        {"many", {0, 0, 0, -1}, 4, "manx"},
        {"rhino", {1, 1, 1, 1, 1}, 5, "sijop"},
        {"abc", {1, 1, 1}, 3, "bcd"},
        {"xyz", {1, 1, 1}, 3, "yza"},
        {"hello", {-1, 0, 1, 0, -1}, 5, "gemln"},
        {"test", {-1, -1, -1, -1}, 4, "sdrs"},
        {"abcd", {1, 2, 3, 4}, 4, "bdfh"},
        {"zzz", {-1, -1, -1}, 3, "yyy"},
        {"world", {0, 1, -1, 2, -2}, 5, "wpqnb"}
    };

    bool all_passed = true;
    for (int i = 0; i < 10; ++i) {
        std::string output = tweakLetters(tests[i].input_word, tests[i].tweaks);
        if (output != tests[i].expected) {
            std::cerr << "Test case " << (i+1) << " FAILED.\n";
            std::cerr << "Input word: " << tests[i].input_word << "\n";
            std::cerr << "Tweaks: ";
            for (int j = 0; j < tests[i].tweaks_len; ++j) std::cerr << tests[i].tweaks[j] << " ";
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
