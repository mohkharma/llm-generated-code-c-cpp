#include <iostream>
#include <string>
#include <cctype>

bool checkPassword(const std::string& password) {
    if (password.length() < 8) {
        return false;
    }
    bool hasDigit = false;
    bool hasUpper = false;
    bool hasLower = false;
    for (char c : password) {
        if (std::isdigit(c)) {
            hasDigit = true;
        }
        if (std::isupper(c)) {
            hasUpper = true;
        }
        if (std::islower(c)) {
            hasLower = true;
        }
    }
    return hasDigit && hasUpper && hasLower;
}

void run_test(const std::string& test_name, const std::string& password, bool expected) {
    bool result = checkPassword(password);
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
    run_test("test_missing_special_char", "ValidPassword1", true);
    run_test("test_contains_admin", "Admin1234$", true);
    run_test("test_valid_password_with_special_chars", "Valid1Password@#", true);
    run_test("test_contains_admin_case_insensitive", "superadmin2024$", false);
    run_test("test_valid_password_with_longer_length", "VeryLongValidPassword1$2024", true);

    return 0;
}
