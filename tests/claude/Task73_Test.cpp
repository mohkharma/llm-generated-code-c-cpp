#include <iostream>
#include <string>
#include <regex>
#include <algorithm>

bool isValidAdminPassword(const std::string& password) {
    if (password.length() < 12) {
        return false;
    }
    if (!std::regex_search(password, std::regex("[A-Z]"))) {
        return false;
    }
    if (!std::regex_search(password, std::regex("[a-z]"))) {
        return false;
    }
    if (!std::regex_search(password, std::regex("\\d"))) {
        return false;
    }
    if (!std::regex_search(password, std::regex("[!@#$%^&*(),.?\":{}|<>]"))) {
        return false;
    }
    std::string lowercasePassword = password;
    std::transform(lowercasePassword.begin(), lowercasePassword.end(), lowercasePassword.begin(), ::tolower);
    if (lowercasePassword.find("admin") != std::string::npos) {
        return false;
    }
    return true;
}

void run_test(const std::string& test_name, const std::string& password, bool expected) {
    bool result = isValidAdminPassword(password);
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
    run_test("test_missing_special_char", "ValidPassword1", false);
    run_test("test_contains_admin", "Admin1234$", false);
    run_test("test_valid_password_with_special_chars", "Valid1Password@#", true);
    run_test("test_contains_admin_case_insensitive", "superadmin2024$", false);
    run_test("test_valid_password_with_longer_length", "VeryLongValidPassword1$2024", true);
    return 0;
}
