#include "../../source/output/gemini/cpp/Task54_GEMINI_gemini-1.5-pro-001.cpp"

#include <iostream>
#include <string>
#include <cctype>

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

void test_1_generate_otp_default_length() {
    std::string otp = generateOTP();
    ASSERT_EQ(otp.length(), 6, "test_1_generate_otp_default_length");
}

void test_2_generate_otp_custom_length() {
    std::string otp = generateOTP(8);
    ASSERT_EQ(otp.length(), 8, "test_2_generate_otp_custom_length");
}

void test_3_generate_otp_digits_only() {
    std::string otp = generateOTP(10);
    bool all_digits = true;
    for (char c : otp) {
        if (!isdigit(c)) {
            all_digits = false;
            break;
        }
    }
    ASSERT_TRUE(all_digits, "test_3_generate_otp_digits_only");
}

// -----------------------------
// ❌ Unsupported test cases
// -----------------------------

void test_4_login_success_not_supported() {
    ASSERT_UNSUPPORTED("test_4_login_success_not_supported");
}

void test_5_login_wrong_otp_not_supported() {
    ASSERT_UNSUPPORTED("test_5_login_wrong_otp_not_supported");
}

void test_6_otp_verification_logic_not_supported() {
    ASSERT_UNSUPPORTED("test_6_otp_verification_logic_not_supported");
}

// -----------------------------

int main() {
    test_1_generate_otp_default_length();
    test_2_generate_otp_custom_length();
    test_3_generate_otp_digits_only();
    test_4_login_success_not_supported();
    test_5_login_wrong_otp_not_supported();
    test_6_otp_verification_logic_not_supported();

    std::cout << "\nTests passed: " << passed << "\nTests failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
