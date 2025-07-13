#include <iostream>
#include <string>
#include <vector>

#include "../../source/output/claude/cpp/Task51_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function

using namespace std;

struct TestCase {
    string input_text;
    int shift;
    string expected_output;
    string description;
};

int main() {
    vector<TestCase> tests = {
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
        string result = encrypt(t.input_text, t.shift);
        if (result == t.expected_output) {
            cout << "Test " << (i + 1) << " (" << t.description << "): PASSED" << endl;
            ++passed;
        } else {
            cout << "Test " << (i + 1) << " (" << t.description << "): FAILED" << endl;
            cout << "  Input: \"" << t.input_text << "\", Shift: " << t.shift << endl;
            cout << "  Expected: \"" << t.expected_output << "\"" << endl;
            cout << "  Got:      \"" << result << "\"" << endl;
            ++failed;
        }
    }

    cout << "--------------------------------" << endl;
    cout << "Total tests: " << tests.size() << ", Passed: " << passed << ", Failed: " << failed << endl;

    return (failed == 0) ? 0 : 1;
}
