#include "../../source/output/codestral/cpp/Task54_MISTRAL_codestral-latest.cpp"

#include <iostream>
#include <string>
#include <sstream>

int passed = 0, failed = 0;

#define ASSERT_EQ(actual, expected, test_name) \
    if ((actual) == (expected)) { \
        std::cout << "[PASS] " << test_name << "\n"; \
        ++passed; \
    } else { \
        std::cout << "[FAIL] " << test_name << "\n"; \
        std::cout << "  Expected: " << expected << "\n"; \
        std::cout << "  Actual  : " << actual << "\n"; \
        ++failed; \
    }

#define ASSERT_NOTE_UNSUPPORTED(test_name) \
    std::cout << "Note: " << test_name << " not supported by this implementation.\n"; \
    std::cout << "[FAIL] " << test_name << "\n"; \
    ++failed;

// ⚠️ ملاحظة: generate_otp() تولد رمزاً عشوائياً جديداً كل مرة، مما يجعل اختبار login صعب التنبؤ.
// لذلك، الاختبارات المتعلقة بـ login و OTP ستكون غير مدعومة حالياً.

void test_generate_otp_length() {
    std::string otp = generate_otp();
    ASSERT_EQ(otp.length(), 6, "test_generate_otp_length");
}

void test_generate_otp_digits_only() {
    std::string otp = generate_otp();
    bool all_digits = true;
    for (char c : otp) {
        if (!isdigit(c)) {
            all_digits = false;
            break;
        }
    }
    ASSERT_EQ(all_digits, true, "test_generate_otp_digits_only");
}

void test_login_success_not_supported() {
    ASSERT_NOTE_UNSUPPORTED("test_login_success_not_supported");
}

void test_login_wrong_otp_not_supported() {
    ASSERT_NOTE_UNSUPPORTED("test_login_wrong_otp_not_supported");
}

void test_login_wrong_username() {
    std::string otp = "000000";  // أي قيمة، لأن username خاطئ
    std::string result = login("admin", "password", otp);
    ASSERT_EQ(result, "Invalid username or password", "test_login_wrong_username");
}

void test_login_wrong_password() {
    std::string otp = "000000";  // أي قيمة، لأن password خاطئ
    std::string result = login("user", "pass", otp);
    ASSERT_EQ(result, "Invalid username or password", "test_login_wrong_password");
}

int main() {
    test_generate_otp_length();
    test_generate_otp_digits_only();
    test_login_success_not_supported();
    test_login_wrong_otp_not_supported();
    test_login_wrong_username();
    test_login_wrong_password();

    std::cout << "\nTests passed: " << passed << "\nTests failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
