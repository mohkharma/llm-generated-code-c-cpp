#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

// دالة لحساب SHA256 وتحويل الناتج إلى Hex string
std::string computeHash(const std::string& password, const std::string& salt) {
    std::string combined = password + salt;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)combined.c_str(), combined.size(), hash);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// دالة اختبار وتحقق من النتائج
void run_test(const std::string& test_name,
              const std::string& password,
              const std::string& salt,
              const std::string& expected,
              bool expect_equal = true) {
    std::string result = computeHash(password, salt);
    bool pass = expect_equal ? (result == expected) : (result != expected);
    std::cout << test_name << ": " << (pass ? "PASS" : "FAIL") << std::endl;
    if (!pass) {
        std::cout << "  Expected: " << expected << std::endl;
        std::cout << "  Got:      " << result << std::endl;
    }
}

int main() {
    std::string password = "mypassword123";
    std::string salt = "randomsalt";
    std::string expected_hash = computeHash(password, salt);

    run_test("test_hash_password_standard_case", password, salt, expected_hash);
    run_test("test_hash_password_empty_password", "", salt, computeHash("", salt));
    run_test("test_hash_password_empty_salt", password, "", computeHash(password, ""));
    run_test("test_hash_password_empty_password_and_salt", "", "", computeHash("", ""));
    run_test("test_hash_password_different_password", "differentpassword", salt, expected_hash, false);
    run_test("test_hash_password_different_salt", password, "differentsalt", expected_hash, false);
    run_test("test_hash_password_different_password_and_salt", "differentpassword", "differentsalt", expected_hash, false);
    run_test("test_hash_password_with_special_characters", "passw@rd!$", "s@lt#", computeHash("passw@rd!$", "s@lt#"));
    run_test("test_hash_password_with_unicode_characters", "p@sswørd", "råndøm$alt", computeHash("p@sswørd", "råndøm$alt"));

    std::string long_password(1000, 'a');
    std::string long_salt(1000, 'b');
    run_test("test_hash_password_long_string", long_password, long_salt, computeHash(long_password, long_salt));

    return 0;
}
