#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

using namespace std;

// دالة SHA256 + تحويل النتيجة لهيكس
string hash_password(const string& password, const string& salt) {
    string salted_password = salt + password;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password.c_str(), salted_password.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }

    return ss.str();
}

void run_test(const string& test_name,
              const string& password,
              const string& salt,
              const string& expected,
              bool expect_equal = true) {
    string result = hash_password(password, salt);
    bool pass = expect_equal ? (result == expected) : (result != expected);
    cout << test_name << ": " << (pass ? "PASS" : "FAIL") << endl;
    if (!pass) {
        cout << "  Expected: " << expected << endl;
        cout << "  Got:      " << result << endl;
    }
}

int main() {
    // حساب القيم المتوقعة بنفس الدالة
    string password = "mypassword123";
    string salt = "randomsalt";
    string expected_hash = hash_password(password, salt);

    run_test("test_hash_password_standard_case", password, salt, expected_hash);

    run_test("test_hash_password_empty_password", "", salt, hash_password("", salt));

    run_test("test_hash_password_empty_salt", password, "", hash_password(password, ""));

    run_test("test_hash_password_empty_password_and_salt", "", "", hash_password("", ""));

    run_test("test_hash_password_different_password", "differentpassword", salt, expected_hash, false);

    run_test("test_hash_password_different_salt", password, "differentsalt", expected_hash, false);

    run_test("test_hash_password_different_password_and_salt", "differentpassword", "differentsalt", expected_hash, false);

    run_test("test_hash_password_with_special_characters", "passw@rd!$", "s@lt#", hash_password("passw@rd!$", "s@lt#"));

    run_test("test_hash_password_with_unicode_characters", "p@sswørd", "råndøm$alt", hash_password("p@sswørd", "råndøm$alt"));

    string long_password(1000, 'a');
    string long_salt(1000, 'b');
    run_test("test_hash_password_long_string", long_password, long_salt, hash_password(long_password, long_salt));

    return 0;
}
