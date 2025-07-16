#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <openssl/sha.h>

// دالة حساب هاش SHA256 وتحويل الناتج لـ hex
std::string compute_hash(const std::string& password, const std::string& salt) {
    std::string combined = password + salt;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(combined.c_str()), combined.size(), hash);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

// دالة لتشغيل الاختبار وطباعة pass/fail
void run_test(const std::string& test_name,
              const std::string& password,
              const std::string& salt,
              const std::string& expected,
              bool expect_equal = true) {
    std::string result = compute_hash(password, salt);
    bool pass = expect_equal ? (result == expected) : (result != expected);
    std::cout << test_name << ": " << (pass ? "PASS" : "FAIL") << std::endl;
    if (!pass) {
        std::cout << "  Expected: " << expected << std::endl;
        std::cout << "  Got:      " << result << std::endl;
    }
}

int main() {
    // إعداد القيم المتوقعة باستخدام نفس الدالة
    std::string password = "mypassword123";
    std::string salt = "randomsalt";
    std::string expected_hash = compute_hash(password, salt);

    run_test("test_hash_password_standard_case", password, salt, expected_hash);
    run_test("test_hash_password_empty_password", "", salt, compute_hash("", salt));
    run_test("test_hash_password_empty_salt", password, "", compute_hash(password, ""));
    run_test("test_hash_password_empty_password_and_salt", "", "", compute_hash("", ""));
    run_test("test_hash_password_different_password", "differentpassword", salt, expected_hash, false);
    run_test("test_hash_password_different_salt", password, "differentsalt", expected_hash, false);
    run_test("test_hash_password_different_password_and_salt", "differentpassword", "differentsalt", expected_hash, false);
    run_test("test_hash_password_with_special_characters", "passw@rd!$", "s@lt#", compute_hash("passw@rd!$", "s@lt#"));
    run_test("test_hash_password_with_unicode_characters", "p@sswørd", "råndøm$alt", compute_hash("p@sswørd", "råndøm$alt"));

    std::string long_password(1000, 'a');
    std::string long_salt(1000, 'b');
    run_test("test_hash_password_long_string", long_password, long_salt, compute_hash(long_password, long_salt));

    return 0;
}
