#include <iostream>
#include <string>
#include <vector>

#include "../../source/output/llama-3/cpp/Task51_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function

struct TestCase {
    std::string input;
    int shift;
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
        {"1234!@#$", 4, "1234!@#$", "encryption non-alpha characters only"}
    };

    int passed = 0;
    int failed = 0;

    for (size_t i = 0; i < tests.size(); ++i) {
        const auto& t = tests[i];
        std::string result = encrypt(t.input, t.shift);
        if (result == t.expected) {
            std::cout << "Test " << (i + 1) << " (" << t.description << "): PASSED\n";
            ++passed;
        } else {
            std::cout << "Test " << (i + 1) << " (" << t.description << "): FAILED\n";
            std::cout << "  Input: \"" << t.input << "\", Shift: " << t.shift << "\n";
            std::cout << "  Expected: \"" << t.expected << "\"\n";
            std::cout << "  Got:      \"" << result << "\"\n";
            ++failed;
        }
    }

    std::cout << "---------------------------------\n";
    std::cout << "Total tests: " << tests.size() << ", Passed: " << passed << ", Failed: " << failed << "\n";

    return (failed == 0) ? 0 : 1;
}
