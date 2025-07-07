#include <iostream>
#include <string>

#include "../../../source/output/llama-3/cpp/Task182_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

 #define clean_phone_number cleanPhoneNumber

int main() {
    int passed = 0;
    const int total = 10;

    struct TestCase {
        std::string input;
        std::string expected;
    };

    TestCase tests[total] = {
        {"+1 (613)-995-0253", "6139950253"},
        {"613-995-0253", "6139950253"},
        {"1 613 995 0253", "6139950253"},
        {"613.995.0253", "6139950253"},
        {"6139950253", "6139950253"},
        {"  +1  613  995  0253  ", "6139950253"},
        {"(613) 995-0253", "6139950253"},
        {"1-613-995-0253", "6139950253"},
        {"1 613.995 0253", "6139950253"},
        {"613 995 0253", "6139950253"}
    };

    for (int i = 0; i < total; ++i) {
        std::string result = clean_phone_number(tests[i].input);
        if (result != tests[i].expected) {
            std::cout << "Test " << (i + 1) << " Failed:\n";
            std::cout << "  Input:    " << tests[i].input << "\n";
            std::cout << "  Expected: " << tests[i].expected << "\n";
            std::cout << "  Got:      " << result << "\n";
            return 1;
        } else {
            passed++;
        }
    }

    std::cout << "All " << passed << " test cases passed!\n";
    return 0;
}
