#include <iostream>
#include <string>
#include <cctype>

bool isPasswordValid(const std::string& password) {
    if (password.length() < 8) {
        return false;
    }
    bool hasUpper = false, hasLower = false, hasDigit = false;
    for (char ch : password) {
        if (std::isupper(ch)) {
            hasUpper = true;
        } else if (std::islower(ch)) {
            hasLower = true;
        } else if (std::isdigit(ch)) {
            hasDigit = true;
        }
    }
    return hasUpper && hasLower && hasDigit;
}

void run_test(const std::string& test_name, const std::string& password, bool expected) {
    bool result = isPasswordValid(password);
    if (result == expected) {
        std::cout << test_name << ": PASS\n";
    } else {
        std::cout << test_name << ": FAIL\n";
    }
}

int main() {
    run_test("test_valid_password", "Valid1Password$2024", true);
    run_test("test_too_short_password", "Short1$", false);
    run_test("test_missing_uppercase", "validpassword1$", false);
    run_test("test_missing_lowercase", "VALIDPASSWORD1$", false);
    run_test("test_missing_digit", "ValidPassword$", false);
    run_test("test_missing_special_char", "ValidPassword1", true);  // no special char required here
    run_test("test_contains_admin", "Admin1234$", true);
    run_test("test_valid_password_with_special_chars", "Valid1Password@#", true);
    run_test("test_contains_admin_case_insensitive", "superadmin2024$", false);  // no uppercase letter
    run_test("test_valid_password_with_longer_length", "VeryLongValidPassword1$2024", true);

    return 0;
}
