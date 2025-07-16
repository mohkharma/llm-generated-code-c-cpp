#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cctype>

// Encryption function as given, no external calls
std::string encrypt_message(const std::string& message, int key) {
    std::vector<char> cipher;
    for (char c = 'A'; c <= 'Z'; ++c) {
        cipher.push_back(c);
    }

    std::mt19937 gen(key);
    std::shuffle(cipher.begin(), cipher.end(), gen);

    std::string encrypted;
    for (char c : message) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            int index = std::toupper(static_cast<unsigned char>(c)) - 'A';
            encrypted += cipher[index];
        } else {
            encrypted += c;
        }
    }

    return encrypted;
}

// Helper function to run test and print pass/fail
void run_test(const std::string& test_name, const std::string& message, int key, const std::string& expected, bool expect_equal=true) {
    std::string result = encrypt_message(message, key);
    bool pass = expect_equal ? (result == expected) : (result != expected);
    std::cout << test_name << ": " << (pass ? "PASS" : "FAIL") << std::endl;
    if (!pass) {
        std::cout << "  Expected: \"" << expected << "\"" << std::endl;
        std::cout << "  Got:      \"" << result << "\"" << std::endl;
    }
}

int main() {
    // The exact test cases from your Python unittest, same expected results

    run_test("test_basic_encryption", "HELLO", 3, "KHOOR");

    run_test("test_encryption_with_spaces", "HELLO WORLD", 5, "QNUXZ DMJFZ");

    run_test("test_encryption_with_special_characters", "HELLO, WORLD!", 2, "RDSSV, UFSVF!");

    run_test("test_empty_message", "", 10, "");

    run_test("test_encryption_with_numbers", "HELLO123", 4, "GDKKN123");

    // test_same_key_produces_same_output
    {
        std::string r1 = encrypt_message("PYTHON", 6);
        std::string r2 = encrypt_message("PYTHON", 6);
        bool pass = (r1 == r2);
        std::cout << "test_same_key_produces_same_output: " << (pass ? "PASS" : "FAIL") << std::endl;
        if (!pass) {
            std::cout << "  Results differ: \"" << r1 << "\" vs \"" << r2 << "\"" << std::endl;
        }
    }

    // test_different_key_produces_different_output
    {
        std::string r1 = encrypt_message("PYTHON", 6);
        std::string r2 = encrypt_message("PYTHON", 8);
        bool pass = (r1 != r2);
        std::cout << "test_different_key_produces_different_output: " << (pass ? "PASS" : "FAIL") << std::endl;
        if (!pass) {
            std::cout << "  Results same: \"" << r1 << "\"" << std::endl;
        }
    }

    run_test("test_case_insensitive_encryption", "Python", 7, "DKSOQD");

    // test_key_affects_shuffling
    {
        std::string r1 = encrypt_message("TEST", 9);
        std::string r2 = encrypt_message("TEST", 10);
        bool pass = (r1 != r2);
        std::cout << "test_key_affects_shuffling: " << (pass ? "PASS" : "FAIL") << std::endl;
        if (!pass) {
            std::cout << "  Results same: \"" << r1 << "\"" << std::endl;
        }
    }

    // test_same_key_and_message_different_cases
    {
        std::string r1 = encrypt_message("test", 11);
        std::string r2 = encrypt_message("TEST", 11);
        bool pass = (r1 == r2);
        std::cout << "test_same_key_and_message_different_cases: " << (pass ? "PASS" : "FAIL") << std::endl;
        if (!pass) {
            std::cout << "  Results differ: \"" << r1 << "\" vs \"" << r2 << "\"" << std::endl;
        }
    }

    return 0;
}
