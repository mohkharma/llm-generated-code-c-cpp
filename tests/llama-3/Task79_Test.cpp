#include <iostream>
#include <map>
#include <string>

std::map<char, char> createCipher(int key) {
    std::map<char, char> cipher;
    for (int i = 0; i < 26; i++) {
        cipher[(char) (65 + i)] = (char) (65 + (i + key) % 26);
        cipher[(char) (97 + i)] = (char) (97 + (i + key) % 26);
    }
    return cipher;
}

std::string encryptMessage(std::string message, int key) {
    std::map<char, char> cipher = createCipher(key);
    std::string encryptedMessage;
    for (char c : message) {
        if (cipher.find(c) != cipher.end()) {
            encryptedMessage += cipher[c];
        } else {
            encryptedMessage += c;
        }
    }
    return encryptedMessage;
}

void run_test(const std::string& test_name, const std::string& message, int key, const std::string& expected) {
    std::string result = encryptMessage(message, key);
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

    // test_same_key_produces_same_output
    {
        std::string r1 = encryptMessage("PYTHON", 6);
        std::string r2 = encryptMessage("PYTHON", 6);
        std::cout << "test_same_key_produces_same_output: " << (r1 == r2 ? "PASS" : "FAIL") << std::endl;
    }

    // test_different_key_produces_different_output
    {
        std::string r1 = encryptMessage("PYTHON", 6);
        std::string r2 = encryptMessage("PYTHON", 8);
        std::cout << "test_different_key_produces_different_output: " << (r1 != r2 ? "PASS" : "FAIL") << std::endl;
    }

    run_test("test_case_insensitive_encryption", "Python", 7, "Wfavuq");

    // test_key_affects_shuffling
    {
        std::string r1 = encryptMessage("TEST", 9);
        std::string r2 = encryptMessage("TEST", 10);
        std::cout << "test_key_affects_shuffling: " << (r1 != r2 ? "PASS" : "FAIL") << std::endl;
    }

    // test_same_key_and_message_different_cases
    {
        std::string r1 = encryptMessage("test", 11);
        std::string r2 = encryptMessage("TEST", 11);
        std::cout << "test_same_key_and_message_different_cases: " << (r1 == r2 ? "PASS" : "FAIL") << std::endl;
    }

    return 0;
}

