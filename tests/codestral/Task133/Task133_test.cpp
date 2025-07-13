#include <iostream>
#include <string>
#include "../../../source/output/codestral/cpp/Task133_MISTRAL_codestral-latest.cpp"

// دالة مساعدة لاختبار resetPassword مع مقارنة النتيجة المتوقعة
bool test_resetPassword(const std::string& currentPwd, const std::string& newPwd, const std::string& confirmPwd, const std::string& expectedMessage) {
    std::string result = resetPassword(currentPwd, newPwd, confirmPwd);
    return result == expectedMessage;
}

int main() {
    int passed = 0, failed = 0;

    // Test case 1: Current password wrong
    if (test_resetPassword("wrongpassword", "new123", "new123", "Current password is incorrect.")) {
        std::cout << "[PASS] Test wrong current password\n";
        passed++;
    } else {
        std::cout << "[FAIL] Test wrong current password\n";
        failed++;
    }

    // Test case 2: New password and confirm password do not match
    if (test_resetPassword("oldpassword", "new123", "different123", "New password and confirm password do not match.")) {
        std::cout << "[PASS] Test new password mismatch\n";
        passed++;
    } else {
        std::cout << "[FAIL] Test new password mismatch\n";
        failed++;
    }

    // Test case 3: Successful password reset
    if (test_resetPassword("oldpassword", "newpassword123", "newpassword123", "Password reset successful.")) {
        std::cout << "[PASS] Test successful password reset\n";
        passed++;
    } else {
        std::cout << "[FAIL] Test successful password reset\n";
        failed++;
    }

    std::cout << "-------------------------\n";
    std::cout << "Passed: " << passed << "\nFailed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
