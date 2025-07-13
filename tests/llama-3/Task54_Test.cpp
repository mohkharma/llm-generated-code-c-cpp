#include "../../source/output/llama-3/cpp/Task54_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

#include <iostream>
#include <string>
#include <cctype>
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
// ✅ Supported tests
// -----------------------------

void test_1_generate_otp_length() {
    std::string otp = generateOTP();
    ASSERT_EQ(otp.length(), 6, "test_1_generate_otp_length");
}

void test_2_generate_otp_digits_only() {
    std::string otp = generateOTP();
    bool all_digits = true;
    for (char c : otp) {
        if (!isdigit(c)) {
            all_digits = false;
            break;
        }
    }
    ASSERT_TRUE(all_digits, "test_2_generate_otp_digits_only");
}

void test_3_authenticate_invalid_user() {
    std::string otp = generateOTP();  // لا يهم لأن username خاطئ
    std::string result = authenticate("user", "password", otp);
    ASSERT_EQ(result, "Authentication failed", "test_3_authenticate_invalid_user");
}

// -----------------------------
// ❌ Unsupported tests due to internal OTP generation in authenticate()
// -----------------------------

void test_4_authenticate_success_not_supported() {
    ASSERT_UNSUPPORTED("test_4_authenticate_success_not_supported");
}

void test_5_authenticate_invalid_otp_not_supported() {
    ASSERT_UNSUPPORTED("test_5_authenticate_invalid_otp_not_supported");
}

void test_6_authenticate_wrong_password_not_supported() {
    ASSERT_UNSUPPORTED("test_6_authenticate_wrong_password_not_supported");
}

// -----------------------------

int main() {
    test_1_generate_otp_length();
    test_2_generate_otp_digits_only();
    test_3_authenticate_invalid_user();
    test_4_authenticate_success_not_supported();
    test_5_authenticate_invalid_otp_not_supported();
    test_6_authenticate_wrong_password_not_supported();

    std::cout << "\nTests passed: " << passed << "\nTests failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
