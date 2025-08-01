#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cstdio>  // For remove()

#include "../../source/output/claude/cpp/Task40_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function

int passed = 0;
int failed = 0;

void printResult(const std::string& testName, bool success) {
    if (success) {
        std::cout << "[PASS] " << testName << "\n";
        passed++;
    } else {
        std::cout << "[FAIL] " << testName << "\n";
        failed++;
    }
}

void test_generate_csrf_token_length() {
    std::string token = generate_csrf_token();
    printResult("test_generate_csrf_token_length", token.length() == 32);
}

void test_save_and_read_token() {
    std::string token = "TEST_TOKEN_1234567890";
    save_csrf_token(token);
    std::string read = read_csrf_token();
    printResult("test_save_and_read_token", read == token);

    // Cleanup
    std::remove("/tmp/csrf_token.txt");
}

void test_parse_query_string_valid() {
    std::string query = "username=ali&email=test@example.com";
    auto result = parse_query_string(query);
    bool success = result["username"] == "ali" && result["email"] == "test@example.com";
    printResult("test_parse_query_string_valid", success);
}

void test_parse_query_string_empty() {
    std::string query = "";
    auto result = parse_query_string(query);
    printResult("test_parse_query_string_empty", result.empty());
}

int main() {
    test_generate_csrf_token_length();
    test_save_and_read_token();
    test_parse_query_string_valid();
    test_parse_query_string_empty();

    std::cout << "\nTests passed: " << passed << "\n";
    std::cout << "Tests failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
