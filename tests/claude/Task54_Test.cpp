#include "../../source/output/claude/cpp/Task54_CLAUDE_claude-3-5-sonnet-20240620.cpp"

#include <iostream>
#include <sstream>
#include <string>

int passed = 0, failed = 0;

#define ASSERT_TRUE(cond, name) \
    if (cond) { \
        std::cout << "[PASS] " << name << "\n"; \
        ++passed; \
    } else { \
        std::cout << "[FAIL] " << name << "\n"; \
        ++failed; \
    }

// ⚠️ ملاحظة: دالة login تعتمد على std::cin و std::cout مباشرة، لذلك سنختبر فقط التوابع القابلة للاختبار منفصلة.

void test_generate_otp_length() {
    std::string otp = generateOTP();
    ASSERT_TRUE(otp.length() == 6, "test_generate_otp_length");
}

void test_generate_otp_digits_only() {
    std::string otp = generateOTP();
    bool all_digits = true;
    for (char c : otp) {
        if (!isdigit(c)) {
            all_digits = false;
            break;
        }
    }
    ASSERT_TRUE(all_digits, "test_generate_otp_digits_only");
}

void test_verify_otp_correct() {
    std::string otp = "123456";
    ASSERT_TRUE(verifyOTP("123456", otp), "test_verify_otp_correct");
}

void test_verify_otp_incorrect() {
    std::string otp = "123456";
    ASSERT_TRUE(!verifyOTP("654321", otp), "test_verify_otp_incorrect");
}

void test_send_otp_output_format() {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    sendOTP("123456");

    std::cout.rdbuf(old); // restore
    std::string output = buffer.str();
    ASSERT_TRUE(output.find("OTP sent: 123456") != std::string::npos, "test_send_otp_output_format");
}

void test_login_not_supported() {
    std::cout << "Note: test_login_not_supported not supported by this implementation.\n";
    ASSERT_TRUE(false, "test_login_not_supported");  // فشل متعمد
}

int main() {
    test_generate_otp_length();
    test_generate_otp_digits_only();
    test_verify_otp_correct();
    test_verify_otp_incorrect();
    test_send_otp_output_format();
    test_login_not_supported();

    std::cout << "\nTests passed: " << passed << "\nTests failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
