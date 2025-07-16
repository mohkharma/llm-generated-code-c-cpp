#include <iostream>
#include <string>
#include <cctype>

// دالة تشفير قيصر (Caesar cipher)
std::string encrypt(const std::string& message, int key) {
    std::string cipher;
    for (char character : message) {
        if (std::isalpha(static_cast<unsigned char>(character))) {
            char shifted = std::isupper(static_cast<unsigned char>(character)) ? 'A' : 'a';
            cipher += (char) ((character - shifted + key) % 26 + shifted);
        } else {
            cipher += character;
        }
    }
    return cipher;
}

// دالة مساعدة للاختبارات
void run_test(const std::string& test_name, const std::string& message, int key, const std::string& expected) {
    std::string result = encrypt(message, key);
    bool pass = (result == expected);
    std::cout << test_name << ": " << (pass ? "PASS" : "FAIL") << std::endl;
    if (!pass) {
        std::cout << "  Expected: \"" << expected << "\"\n";
        std::cout << "  Got:      \"" << result << "\"\n";
    }
}

int main() {
    run_test("test_basic_encryption", "HELLO", 3, "KHOOR");
    run_test("test_encryption_with_spaces", "HELLO WORLD", 5, "MJQQT BTWQI");
    run_test("test_encryption_with_special_characters", "HELLO, WORLD!", 2, "JGNNQ, YQTNF!");
    run_test("test_empty_message", "", 10, "");
    run_test("test_encryption_with_numbers", "HELLO123", 4, "LIPPS123");
    // نفس المفتاح ينتج نفس الناتج
    {
        std::string r1 = encrypt("PYTHON", 6);
        std::string r2 = encrypt("PYTHON", 6);
        std::cout << "test_same_key_produces_same_output: " << (r1 == r2 ? "PASS" : "FAIL") << std::endl;
    }
    // مفتاح مختلف ينتج ناتج مختلف
    {
        std::string r1 = encrypt("PYTHON", 6);
        std::string r2 = encrypt("PYTHON", 8);
        std::cout << "test_different_key_produces_different_output: " << (r1 != r2 ? "PASS" : "FAIL") << std::endl;
    }
    run_test("test_case_insensitive_encryption", "Python", 7, "Wfavuq");
    // المفتاح يؤثر على النتيجة
    {
        std::string r1 = encrypt("TEST", 9);
        std::string r2 = encrypt("TEST", 10);
        std::cout << "test_key_affects_shuffling: " << (r1 != r2 ? "PASS" : "FAIL") << std::endl;
    }
    // نفس المفتاح ونفس الرسالة بحروف صغيرة وكبيرة ينتج نفس الناتج
    {
        std::string r1 = encrypt("test", 11);
        std::string r2 = encrypt("TEST", 11);
        std::cout << "test_same_key_and_message_different_cases: " << (r1 != r2 ? "FAIL" : "PASS") << std::endl;
    }
    return 0;
}
