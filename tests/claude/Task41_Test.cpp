#include <iostream>
#include <sstream>
#include <string>

#include "../../source/output/claude/cpp/Task41_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function

int passed = 0, failed = 0;

void run_test(const std::string& test_name, const std::string& input, const std::string& expected_output) {
    std::ostringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    processInput(input);

    std::cout.rdbuf(old); // استرجاع المخرجات الأصلية
    std::string output = buffer.str();

    // حذف نهاية السطر إن وجدت
    while (!output.empty() && (output.back() == '\n' || output.back() == '\r'))
        output.pop_back();

    if (output == expected_output) {
        std::cout << "[PASS] " << test_name << "\n";
        passed++;
    } else {
        std::cout << "[FAIL] " << test_name << "\n"
                  << "Expected: \"" << expected_output << "\"\n"
                  << "Got     : \"" << output << "\"\n";
        failed++;
    }
}

int main() {
    run_test("test_normal_input", "Hello, world!", "Processed input: Hello, world!");

    std::string input_100(100, 'a');
    run_test("test_input_100_chars", input_100, "Processed input: " + input_100);

    std::string input_150(150, 'a');
    run_test("test_input_longer_than_100_chars", input_150.substr(0, 100), "Processed input: " + input_150.substr(0, 100));

    run_test("test_empty_input", "", "Processed input: ");
    run_test("test_input_special_chars", "@#$%^&*()", "Processed input: @#$%^&*()");
    run_test("test_numeric_input", "1234567890", "Processed input: 1234567890");
    run_test("test_mixed_input", "Hello123", "Processed input: Hello123");
    run_test("test_whitespace_input", "     ", "Processed input:      ");
    run_test("test_newline_input", "Hello\nWorld", "Processed input: Hello\nWorld");
    run_test("test_leading_trailing_spaces", "  Hello  ", "Processed input:   Hello  ");

    std::cout << "\nTests passed: " << passed << "\nTests failed: " << failed << std::endl;
    return failed == 0 ? 0 : 1;
}
