#include "../../source/output/claude/cpp/Task56_CLAUDE_claude-3-5-sonnet-20240620.cpp"
#include <iostream>
#include <string>
#include <cctype>

int tests_run = 0;
int tests_passed = 0;

#define ASSERT_TRUE(condition) \
do { \
++tests_run; \
if (condition) { \
std::cout << "[PASS] " << __func__ << "\n"; \
++tests_passed; \
} else { \
std::cout << "[FAIL] " << __func__ << "\n"; \
} \
} while(0)

bool isValidToken(const std::string& token) {
    for (char c : token) {
        if (!std::isalnum(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

void test_default_length_token() {
    std::string token = generate_token();
    ASSERT_TRUE(token.length() == 32);
}

void test_custom_length_token_16() {
    std::string token = generate_token(16);
    ASSERT_TRUE(token.length() == 16);
}

void test_custom_length_token_64() {
    std::string token = generate_token(64);
    ASSERT_TRUE(token.length() == 64);
}

void test_token_characters_are_valid() {
    std::string token = generate_token(100);
    ASSERT_TRUE(isValidToken(token));
}

int main() {
    test_default_length_token();
    test_custom_length_token_16();
    test_custom_length_token_64();
    test_token_characters_are_valid();

    std::cout << "\nTotal tests run: " << tests_run << "\n";
    std::cout << "Total tests passed: " << tests_passed << "\n";
    std::cout << "Total tests failed: " << (tests_run - tests_passed) << "\n";

    return 0;
}
