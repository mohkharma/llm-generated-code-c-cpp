#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

// دالة sha256 لحساب هاش
std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// دالة hashPassword التي تجمع كلمة السر والملح ثم تحسب الهاش
std::string hashPassword(const std::string& password, const std::string& salt) {
    return sha256(password + salt);
}

// دالة لتشغيل التست وطباعة النتيجة
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
    // إعداد القيم المشتركة للتوقعات (مطابقة بايثون)
    std::string password = "mypassword123";
    std::string salt = "randomsalt";
    std::string expected_hash = sha256(password + salt);

    run_test("test_hash_password_standard_case", password, salt, expected_hash);

    run_test("test_hash_password_empty_password", "", salt, sha256(salt));

    run_test("test_hash_password_empty_salt", password, "", sha256(password));

    run_test("test_hash_password_empty_password_and_salt", "", "", sha256(""));

    run_test("test_hash_password_different_password", "differentpassword", salt, expected_hash, false);

    run_test("test_hash_password_different_salt", password, "differentsalt", expected_hash, false);

    run_test("test_hash_password_different_password_and_salt", "differentpassword", "differentsalt", expected_hash, false);

    run_test("test_hash_password_with_special_characters", "passw@rd!$", "s@lt#", sha256("passw@rd!$s@lt#"));

    run_test("test_hash_password_with_unicode_characters", "p@sswørd", "råndøm$alt", sha256("p@sswørdråndøm$alt"));

    std::string long_password(1000, 'a');
    std::string long_salt(1000, 'b');
    run_test("test_hash_password_long_string", long_password, long_salt, sha256(long_password + long_salt));

    return 0;
}
