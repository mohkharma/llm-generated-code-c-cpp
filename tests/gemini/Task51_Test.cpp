#include <iostream>
#include <string>
#include <vector>

#include "../../source/output/gemini/cpp/Task51_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function

struct TestCase {
    std::string input;
    int key;
    std::string expected;
    std::string description;
};

int main() {
    std::vector<TestCase> tests = {
        {"abc", 3, "def", "basic encryption"},
        {"ABC", 3, "DEF", "encryption with uppercase"},
        {"aBc", 2, "cDe", "encryption with mixed case"},
        {"a b-c", 5, "f g-h", "encryption with non-alpha characters"},
        {"xyz", 30, "bcd", "encryption with large shift value"},
        {"def", -3, "abc", "encryption with negative shift value"},
        {"hello", 0, "hello", "encryption with shift value zero"},
        {"xyz", 26, "xyz", "encryption with shift value 26"},
        {"", 5, "", "encryption empty string"},
        {"1234!@#$", 4, "5678!@#$", "encryption with digits and non-alpha characters"}
    };

    int passed = 0;
    int failed = 0;

    for (size_t i = 0; i < tests.size(); ++i) {
        const auto& t = tests[i];
        std::string result = encrypt(t.input, t.key);
        if (result == t.expected) {
            std::cout << "Test " << (i + 1) << " (" << t.description << "): PASSED\n";
            ++passed;
        } else {
            std::cout << "Test " << (i + 1) << " (" << t.description << "): FAILED\n";
            std::cout << "  Input: \"" << t.input << "\", Key: " << t.key << "\n";
            std::cout << "  Expected: \"" << t.expected << "\"\n";
            std::cout << "  Got:      \"" << result << "\"\n";
            ++failed;
        }
    }

    std::cout << "---------------------------------\n";
    std::cout << "Total tests: " << tests.size() << ", Passed: " << passed << ", Failed: " << failed << "\n";

    return (failed == 0) ? 0 : 1;
}
