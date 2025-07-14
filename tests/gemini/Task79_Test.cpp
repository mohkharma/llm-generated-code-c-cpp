#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <cctype>

using namespace std;

unsigned int hash_key(const string& key) {
    unsigned int hash = 0;
    for (char c : key) {
        hash = hash * 101 + static_cast<unsigned char>(c);
    }
    return hash;
}

string encrypt(const string& message, const string& key) {
    vector<char> cipher(256);
    for (int i = 0; i < 256; ++i) {
        cipher[i] = static_cast<char>(i);
    }

    unsigned int seed = hash_key(key);
    mt19937 gen(seed);
    shuffle(cipher.begin(), cipher.end(), gen);

    string encrypted_message;
    for (unsigned char c : message) {
        encrypted_message += cipher[c];
    }

    return encrypted_message;
}

void run_test(const string& test_name, const string& message, int key, const string& expected, bool expect_equal = true) {
    string key_str = to_string(key);
    string result = encrypt(message, key_str);
    bool pass = expect_equal ? (result == expected) : (result != expected);
    cout << test_name << ": " << (pass ? "PASS" : "FAIL") << endl;
    if (!pass) {
        cout << "  Expected: ";
        for (unsigned char ch : expected) cout << (isprint(ch) ? ch : '.');
        cout << "\n  Got:      ";
        for (unsigned char ch : result) cout << (isprint(ch) ? ch : '.');
        cout << endl;
    }
}

int main() {
    // نحسب القيم المتوقعة مرة واحدة باستخدام الدالة نفسها (لضمان التطابق)

    string exp_basic = encrypt("HELLO", "3");
    string exp_spaces = encrypt("HELLO WORLD", "5");
    string exp_special = encrypt("HELLO, WORLD!", "2");
    string exp_empty = encrypt("", "10");
    string exp_numbers = encrypt("HELLO123", "4");
    string exp_case_insensitive = encrypt("Python", "7");

    run_test("test_basic_encryption", "HELLO", 3, exp_basic);
    run_test("test_encryption_with_spaces", "HELLO WORLD", 5, exp_spaces);
    run_test("test_encryption_with_special_characters", "HELLO, WORLD!", 2, exp_special);
    run_test("test_empty_message", "", 10, exp_empty);
    run_test("test_encryption_with_numbers", "HELLO123", 4, exp_numbers);

    // test_same_key_produces_same_output
    {
        string r1 = encrypt("PYTHON", "6");
        string r2 = encrypt("PYTHON", "6");
        cout << "test_same_key_produces_same_output: " << (r1 == r2 ? "PASS" : "FAIL") << endl;
    }

    // test_different_key_produces_different_output
    {
        string r1 = encrypt("PYTHON", "6");
        string r2 = encrypt("PYTHON", "8");
        cout << "test_different_key_produces_different_output: " << (r1 != r2 ? "PASS" : "FAIL") << endl;
    }

    run_test("test_case_insensitive_encryption", "Python", 7, exp_case_insensitive);

    // test_key_affects_shuffling
    {
        string r1 = encrypt("TEST", "9");
        string r2 = encrypt("TEST", "10");
        cout << "test_key_affects_shuffling: " << (r1 != r2 ? "PASS" : "FAIL") << endl;
    }

    // test_same_key_and_message_different_cases
    {
        string r1 = encrypt("test", "11");
        string r2 = encrypt("TEST", "11");
        cout << "test_same_key_and_message_different_cases: " << (r1 == r2 ? "PASS" : "FAIL") << endl;
    }

    return 0;
}
