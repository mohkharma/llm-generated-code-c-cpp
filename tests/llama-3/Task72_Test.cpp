#include "../../source/output/llama-3/cpp/Task72_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

#include <iostream>
#include <sstream>
#include <string>

bool run_test(const std::string& input, const std::string& key, const std::string& expected_hex, const std::string& test_name) {
    // إنشاء stream مؤقت وتهيئة
    std::ostringstream oss;
    std::streambuf* original_buf = std::cout.rdbuf();  // حفظ المخزن الأصلي
    std::cout.rdbuf(oss.rdbuf());                      // إعادة توجيه cout

    encryptAndPrintHex(input, key);                    // استدعاء الدالة
    std::cout.flush();                                 // تفريغ buffer إلى oss

    std::cout.rdbuf(original_buf);                     // استعادة المخزن الأصلي

    std::string actual_hex = oss.str();
    if (!actual_hex.empty() && actual_hex.back() == '\n') {
        actual_hex.pop_back();  // إزالة السطر الأخير إن وُجد
    }

    if (actual_hex == expected_hex) {
        std::cout << "[PASS] " << test_name << "\n";
        return true;
    } else {
        std::cout << "[FAIL] " << test_name << "\nExpected: " << expected_hex << "\nGot     : " << actual_hex << "\n";
        return false;
    }
}

int main() {
    int passed = 0, failed = 0;

    // test_1_encrypt_known_input
    {
        std::string input = "This is a secret message.";
        std::string key = "0123456789abcdef";
        std::string expected_hex = "d7b9e6744633c9a0689defbb7513e9988ed7bb5b9fe6de33947fca8e68342483";

        if (run_test(input, key, expected_hex, "test_1_encrypt_known_input")) passed++;
        else failed++;
    }

    // test_2_encrypt_empty_input
    {
        std::string input = "";
        std::string key = "aaaaaaaaaaaaaaaa";
        std::string expected_hex = "c9056aeaa4571a5b30918e0d9a197b97";

        if (run_test(input, key, expected_hex, "test_2_encrypt_empty_input")) passed++;
        else failed++;
    }

    std::cout << "\nTests passed: " << passed << "\nTests failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
