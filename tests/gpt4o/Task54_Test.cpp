#include "../../source/output/gpt4o/cpp/Task54_OPENAI_gpt-4o.cpp"

#include <iostream>
#include <ctime>

int passed = 0, failed = 0;

#define ASSERT_TRUE(cond, name) \
    if (cond) { \
        std::cout << "[PASS] " << name << "\n"; \
        ++passed; \
    } else { \
        std::cout << "[FAIL] " << name << "\n"; \
        ++failed; \
    }

#define ASSERT_EQ(val1, val2, name) \
    if ((val1) == (val2)) { \
        std::cout << "[PASS] " << name << "\n"; \
        ++passed; \
    } else { \
        std::cout << "[FAIL] " << name << "\n"; \
        std::cout << "  Expected: " << val2 << "\n"; \
        std::cout << "  Actual  : " << val1 << "\n"; \
        ++failed; \
    }

#define ASSERT_UNSUPPORTED(name) \
    std::cout << "Note: " << name << " not supported by this implementation.\n"; \
    ASSERT_TRUE(false, name);

// -----------------------------
// ✅ Supported test cases
// -----------------------------

void test_1_generate_otp_range() {
    std::srand(static_cast<unsigned int>(std::time(0)));  // Seed for std::rand
    int otp = generateOTP();
    ASSERT_TRUE(otp >= 100000 && otp <= 999999, "test_1_generate_otp_range");
}

void test_2_verify_otp_success() {
    int otp = 123456;
    ASSERT_TRUE(verifyOTP(123456, otp), "test_2_verify_otp_success");
}

void test_3_verify_otp_failure() {
    int otp = 123456;
    ASSERT_TRUE(!verifyOTP(654321, otp), "test_3_verify_otp_failure");
}

// -----------------------------
// ❌ Unsupported test cases
// -----------------------------

void test_4_login_not_supported() {
    ASSERT_UNSUPPORTED("test_4_login_not_supported");
}

void test_5_generate_string_otp_not_supported() {
    ASSERT_UNSUPPORTED("test_5_generate_string_otp_not_supported");
}

void test_6_email_sending_not_supported() {
    ASSERT_UNSUPPORTED("test_6_email_sending_not_supported");
}

// -----------------------------

int main() {
    test_1_generate_otp_range();
    test_2_verify_otp_success();
    test_3_verify_otp_failure();
    test_4_login_not_supported();
    test_5_generate_string_otp_not_supported();
    test_6_email_sending_not_supported();

    std::cout << "\nTests passed: " << passed << "\nTests failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
