#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>

// دالة توليد توكن نصي عشوائي من 32 محرف هيكس (محاكاة UUID)
std::string generateMockCsrfToken() {
    static const char hex_chars[] = "0123456789abcdef";
    std::string token;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);

    for (int i = 0; i < 32; ++i) {
        token += hex_chars[dis(gen)];
    }
    return token;
}

 bool validateToken(const std::string& token, const std::string& expected) {
    return token == expected;
}

int main() {
    int passed = 0;
    int failed = 0;

    // توليد توكن
    std::string token = generateMockCsrfToken();

    // اختبار 1: طول التوكن 32 والهيكس فقط
    bool valid_format = (token.length() == 32);
    for (char c : token) {
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) {
            valid_format = false;
            break;
        }
    }
    if (valid_format) {
        std::cout << "[PASS] Test 1: Token format valid\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Test 1: Token format invalid: " << token << "\n";
        ++failed;
    }

    // اختبار 2: تحقق صحيح بتوكن مطابق
    if (validateToken(token, token)) {
        std::cout << "[PASS] Test 2: Token validation succeeds for matching tokens\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Test 2: Token validation failed for matching tokens\n";
        ++failed;
    }

    // اختبار 3: تحقق خاطئ بتوكن مختلف
    if (!validateToken(token, "wrongtoken0123456789abcdef01234567")) {
        std::cout << "[PASS] Test 3: Token validation fails for non-matching tokens\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Test 3: Token validation incorrectly passed for non-matching tokens\n";
        ++failed;
    }

    std::cout << "---------------------------\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
