#include <iostream>
#include <sstream>
#include <string>

#include "../../source/output/llama-3/cpp/Task41_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // LLaMA الحل

int passed = 0, failed = 0;

void run_test(const std::string& test_name, const std::string& simulated_input, const std::string& expected_output) {
    std::istringstream input_stream(simulated_input);
    std::ostringstream output_stream;

    // حفظ المخرجات الأصلية
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::streambuf* cout_backup = std::cout.rdbuf();

    // إعادة توجيه cin و cout
    std::cin.rdbuf(input_stream.rdbuf());
    std::cout.rdbuf(output_stream.rdbuf());

    printUserInput();  // الدالة من الحل

    // استرجاع التدفقات الأصلية
    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    std::string output = output_stream.str();

    // إزالة نهايات السطر الزائدة
    while (!output.empty() && (output.back() == '\n' || output.back() == '\r'))
        output.pop_back();

    std::string cleaned_expected = expected_output;
    while (!cleaned_expected.empty() && (cleaned_expected.back() == '\n' || cleaned_expected.back() == '\r'))
        cleaned_expected.pop_back();

    if (output == cleaned_expected) {
        std::cout << "[PASS] " << test_name << "\n";
        passed++;
    } else {
        std::cout << "[FAIL] " << test_name << "\n"
                  << "Expected:\n" << cleaned_expected << "\n"
                  << "Got:\n" << output << "\n";
        failed++;
    }
}

std::string format_expected_output(const std::string& input) {
    return "Enter a string: You entered: " + input;
}

int main() {
    run_test("test_normal_input", "Hello, world!\n", format_expected_output("Hello, world!"));

    std::string input_100(100, 'a');
    run_test("test_input_100_chars", input_100 + "\n", format_expected_output(input_100));

    std::string input_150(150, 'a');
    run_test("test_input_longer_than_100_chars", input_150 + "\n", format_expected_output(input_150.substr(0, 100)));

    run_test("test_empty_input", "\n", format_expected_output(""));
    run_test("test_input_special_chars", "@#$%^&*()\n", format_expected_output("@#$%^&*()"));
    run_test("test_numeric_input", "1234567890\n", format_expected_output("1234567890"));
    run_test("test_mixed_input", "Hello123\n", format_expected_output("Hello123"));
    run_test("test_whitespace_input", "     \n", format_expected_output("     "));
    run_test("test_newline_input", "Hello\n", format_expected_output("Hello"));
    run_test("test_leading_trailing_spaces", "  Hello  \n", format_expected_output("  Hello  "));

    std::cout << "\nTests passed: " << passed << "\nTests failed: " << failed << std::endl;
    return failed == 0 ? 0 : 1;
}
