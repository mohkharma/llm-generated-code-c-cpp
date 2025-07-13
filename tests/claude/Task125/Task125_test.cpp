#include "../../../source/output/claude/cpp/Task125_CLAUDE_claude-3-5-sonnet-20240620.cpp"
#include <iostream>
#include <string>
#include <sstream>

int passed = 0, failed = 0;

void assertTrue(bool result, const std::string& testName) {
    if (result) {
        std::cout << "[PASSED] " << testName << "\n";
        passed++;
    } else {
        std::cout << "[FAILED] " << testName << "\n";
        std::cout << "  Expected: true, Got: false\n";
        failed++;
    }
}

void assertFalse(bool result, const std::string& testName) {
    if (!result) {
        std::cout << "[PASSED] " << testName << "\n";
        passed++;
    } else {
        std::cout << "[FAILED] " << testName << "\n";
        std::cout << "  Expected: false, Got: true\n";
        failed++;
    }
}

 bool authenticate(const std::string& username, const std::string& password) {
    return (username == "admin" && password == "password123");
}

int main() {
    assertTrue(authenticate("admin", "password123"), "test_valid_credentials");

    assertFalse(authenticate("admin", "wrongpassword"), "test_invalid_password");

    assertFalse(authenticate("wronguser", "password123"), "test_invalid_username");

    assertFalse(authenticate("wronguser", "wrongpassword"), "test_invalid_username_and_password");

    assertFalse(authenticate("admin", ""), "test_empty_password");

    assertFalse(authenticate("", "password123"), "test_empty_username");

    assertFalse(authenticate("", ""), "test_empty_username_and_password");

    assertFalse(authenticate(" admin ", "password123"), "test_valid_username_with_extra_spaces");

    assertFalse(authenticate("admin", " password123 "), "test_valid_password_with_extra_spaces");

    assertFalse(authenticate("admin ", " password123"), "test_valid_credentials_with_trailing_spaces");

    // Summary
    std::cout << "\n=== TEST SUMMARY ===\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
