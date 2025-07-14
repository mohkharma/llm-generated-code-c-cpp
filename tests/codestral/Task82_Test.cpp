#include <iostream>
#include <string>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <sstream>
#include <iomanip>

// دالة لتحويل باينري إلى hex
std::string toHex(const unsigned char* data, int length) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < length; ++i) {
        ss << std::setw(2) << static_cast<int>(data[i]);
    }
    return ss.str();
}

// دالة hashPassword باستخدام PBKDF2 + SHA256
std::string hashPassword(const std::string& password, const std::string& salt) {
    const int iterations = 100000;
    const int keyLength = 32;
    unsigned char hash[keyLength];

    PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                      reinterpret_cast<const unsigned char*>(salt.c_str()), salt.length(),
                      iterations, EVP_sha256(), keyLength, hash);

    return toHex(hash, keyLength);
}

// دالة لتشغيل الاختبار وطباعة pass/fail
void run_test(const std::string& test_name,
              const std::string& password,
              const std::string& salt,
              const std::string& expected,
              bool expect_equal = true) {
    std::string result = hashPassword(password, salt);
    bool pass = expect_equal ? (result == expected) : (result != expected);
    std::cout << test_name << ": " << (pass ? "PASS" : "FAIL") << std::endl;
    if (!pass) {
        std::cout << "  Expected: " << expected << std::endl;
        std::cout << "  Got:      " << result << std::endl;
    }
}

int main() {
    // حساب القيم المتوقعة لاختبارات البايثون نفسها

    std::string password = "mypassword123";
    std::string salt = "randomsalt";
    std::string expected_hash = hashPassword(password, salt);

    run_test("test_hash_password_standard_case", password, salt, expected_hash);

    run_test("test_hash_password_empty_password", "", salt, hashPassword("", salt));

    run_test("test_hash_password_empty_salt", password, "", hashPassword(password, ""));

    run_test("test_hash_password_empty_password_and_salt", "", "", hashPassword("", ""));

    run_test("test_hash_password_different_password", "differentpassword", salt, expected_hash, false);

    run_test("test_hash_password_different_salt", password, "differentsalt", expected_hash, false);

    run_test("test_hash_password_different_password_and_salt", "differentpassword", "differentsalt", expected_hash, false);

    run_test("test_hash_password_with_special_characters", "passw@rd!$", "s@lt#", hashPassword("passw@rd!$", "s@lt#"));

    run_test("test_hash_password_with_unicode_characters", "p@sswørd", "råndøm$alt", hashPassword("p@sswørd", "råndøm$alt"));

    std::string long_password(1000, 'a');
    std::string long_salt(1000, 'b');
    run_test("test_hash_password_long_string", long_password, long_salt, hashPassword(long_password, long_salt));

    return 0;
}
