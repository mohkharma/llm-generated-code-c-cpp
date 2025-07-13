#include <iostream>
#include <string>
#include <vector>

#include "../../source/output/gpt4o/cpp/Task51_OPENAI_gpt-4o.cpp"  // Include the header for the function

struct TestCase {
    std::string input;
    std::string expected;
    std::string description;
};

int main() {
    std::vector<TestCase> tests = {
        {"abc", "bcd", "basic encryption by shift 1"},
        {"ABC", "BCD", "encryption uppercase by shift 1"},
        {"aBc", "bCd", "encryption mixed case"},
        {"a b-c", "b c-d", "encryption with non-alpha characters"},
        {"xyz", "yza", "encryption wrap around"},
        {"Hello, World!", "Ifmmp, Xpsme!", "encryption with punctuation"},
        {"", "", "encryption empty string"},
        {"1234!@#$", "1234!@#$", "non-alpha characters unchanged"}
    };

    int passed = 0;
    int failed = 0;

    for (size_t i = 0; i < tests.size(); ++i) {
        const auto& t = tests[i];
        std::string result = encrypt(t.input);
        if (result == t.expected) {
            std::cout << "Test " << (i + 1) << " (" << t.description << "): PASSED\n";
            ++passed;
        } else {
            std::cout << "Test " << (i + 1) << " (" << t.description << "): FAILED\n";
            std::cout << "  Input: \"" << t.input << "\"\n";
            std::cout << "  Expected: \"" << t.expected << "\"\n";
            std::cout << "  Got:      \"" << result << "\"\n";
            ++failed;
        }
    }

    std::cout << "---------------------------------\n";
    std::cout << "Total tests: " << tests.size() << ", Passed: " << passed << ", Failed: " << failed << "\n";

    return (failed == 0) ? 0 : 1;
}
