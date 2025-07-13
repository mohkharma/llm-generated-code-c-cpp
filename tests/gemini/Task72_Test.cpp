#include "../../source/output/gemini/cpp/Task72_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>

// تحويل bytes إلى hex
std::string to_hex(const std::vector<unsigned char>& data) {
    std::ostringstream oss;
    for (auto b : data) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)b;
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
        const std::string plaintext = "This is a secret message.";
        const unsigned char key[16] = {
            0x00, 0x01, 0x02, 0x03,
            0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0a, 0x0b,
            0x0c, 0x0d, 0x0e, 0x0f
        };
        const unsigned char iv[16] = {
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00
        };

        auto result = encryptData(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size(), key, iv);

        std::string expected_hex = "da3a36e4e62c60553df1a5fe1e156fa6630081d6e951d4c9ed50b8a76ecb76e1";

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
        const std::string plaintext = "";
        const unsigned char key[16] = {
            0x01, 0x01, 0x01, 0x01,
            0x01, 0x01, 0x01, 0x01,
            0x01, 0x01, 0x01, 0x01,
            0x01, 0x01, 0x01, 0x01
        };
        const unsigned char iv[16] = {
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00
        };

        auto result = encryptData(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size(), key, iv);

        std::string expected_hex = "7ca514f36aa6d0307b191f2b8c001f84";

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
