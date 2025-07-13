#include "../../source/output/claude/cpp/Task72_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <openssl/aes.h>

// تحويل vector إلى hex string
std::string to_hex(const std::vector<unsigned char>& data) {
    std::ostringstream oss;
    for (unsigned char byte : data) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    return oss.str();
}

bool compare_outputs(const std::vector<unsigned char>& result, const std::string& expected_hex) {
    return to_hex(result) == expected_hex;
}

int main() {
    int passed = 0, failed = 0;

    // test_1_encrypt_known_input
    {
        std::string test_name = "test_1_encrypt_known_input";
        std::string input = "This is a secret message.";
        std::vector<unsigned char> key = {
            0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe,
            0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
            0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7,
            0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4
        };

        auto result = encrypt_data(input, key);

        // ناتج الكود الأصلي (بدون PKCS#7 padding) = تم توليده باستخدام نفس الكود بدون تعديل
        std::string expected_hex = "b761635f269abd82ba4d10b9dad0375963bce8a00d07b67b0e7ac95c9837ce95";

        if (compare_outputs(result, expected_hex)) {
            std::cout << "[PASS] " << test_name << "\n";
            passed++;
        } else {
            std::cout << "[FAIL] " << test_name << "\nExpected: " << expected_hex << "\nGot     : " << to_hex(result) << "\n";
            failed++;
        }
    }

    // test_2_encrypt_empty_input
    {
        std::string test_name = "test_2_encrypt_empty_input";
        std::string input = "";
        std::vector<unsigned char> key(32, 0x01);

        auto result = encrypt_data(input, key);

        // لا يوجد بيانات ولا padding → الناتج سيكون فارغ
        std::string expected_hex = "";

        if (compare_outputs(result, expected_hex)) {
            std::cout << "[PASS] " << test_name << "\n";
            passed++;
        } else {
            std::cout << "[FAIL] " << test_name << "\nExpected: " << expected_hex << "\nGot     : " << to_hex(result) << "\n";
            failed++;
        }
    }

    std::cout << "\nTests passed: " << passed << "\nTests failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
