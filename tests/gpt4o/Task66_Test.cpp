#include "../../source/output/gpt4o/cpp/Task66_OPENAI_gpt-4o.cpp"

#include <iostream>
#include <sstream>
#include <string>

int passed = 0, failed = 0;

#define ASSERT_TRUE(cond) \
if (cond) { \
std::cout << "[PASS] " << __func__ << "\n"; \
++passed; \
} else { \
std::cout << "[FAIL] " << __func__ << "\n"; \
++failed; \
}

void test_1_validate_command_not_supported() {
    std::cout << "Note: test_1_validate_command_not_supported not supported by this implementation.\n";
    ASSERT_TRUE(false);
}

void test_2_run_safe_command() {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    runBashCommand("echo Hello GPT");

    std::cout.rdbuf(oldCout);
    std::string output = buffer.str();
    ASSERT_TRUE(output.find("Command output: Hello GPT") != std::string::npos);
}

void test_3_run_invalid_command() {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    runBashCommand("some_nonexistent_command_456");

    std::cout.rdbuf(oldCout);
    std::string output = buffer.str();
    // حتى لو النتيجة فارغة، يجب أن يكون هناك سطر Command output:
    ASSERT_TRUE(output.find("Command output:") != std::string::npos);
}

void test_4_timeout_not_supported() {
    std::cout << "Note: test_4_timeout_not_supported not supported by this implementation.\n";
    ASSERT_TRUE(false);
}

int main() {
    test_1_validate_command_not_supported();
    test_2_run_safe_command();
    test_3_run_invalid_command();
    test_4_timeout_not_supported();

    std::cout << "\nTests passed: " << passed << "\nTests failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
