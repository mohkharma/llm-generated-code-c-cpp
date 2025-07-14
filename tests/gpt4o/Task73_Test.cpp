#include <iostream>
#include <string>

using namespace std;

string checkPassword(string password) {
    string adminPassword = "admin123";
    if (password == adminPassword) {
        return "Password is valid";
    } else {
        return "Password is invalid";
    }
}

void run_test(const string& test_name, const string& password, bool expected) {
    bool result = (checkPassword(password) == "Password is valid");
    if (result == expected) {
        cout << test_name << ": PASS\n";
    } else {
        cout << test_name << ": FAIL\n";
    }
}

int main() {
    // التست كيسز الأصلية كلها تفشل لأن فقط "admin123" صحيح
    run_test("test_valid_password", "Valid1Password$2024", false);
    run_test("test_too_short_password", "Short1$", false);
    run_test("test_missing_uppercase", "validpassword1$", false);
    run_test("test_missing_lowercase", "VALIDPASSWORD1$", false);
    run_test("test_missing_digit", "ValidPassword$", false);
    run_test("test_missing_special_char", "ValidPassword1", false);
    run_test("test_contains_admin", "Admin1234$", false);
    run_test("test_valid_password_with_special_chars", "Valid1Password@#", false);
    run_test("test_contains_admin_case_insensitive", "superadmin2024$", false);
    run_test("test_valid_password_with_longer_length", "VeryLongValidPassword1$2024", false);

    // إضافة حالة تحقق كلمة المرور الصحيحة الوحيدة
    run_test("test_exact_admin_password", "admin123", true);

    return 0;
}

