#include <iostream>
#include <sstream>
#include <string>
#include "../../../source/output/gemini/cpp/Task134_GEMINI_gemini-1.5-pro-001.cpp"
 
bool test_crypto_aes_256_cbc() {
    const std::string originalMessage = "Hello, World!";

    // توليد المفتاح - لا نفترض أي حجم أو تنسيق
    std::string key = generateKey(32); // 32 بايت (حسب توقيع دالتك)

    if (key.empty()) {
        std::cerr << "[FAIL] Generated key is empty\n";
        return false;
    }

    // تشفير النص
    std::string encrypted = encryptMessage(originalMessage, key);
    if (encrypted.empty()) {
        std::cerr << "[FAIL] Encryption returned empty ciphertext\n";
        return false;
    }

    // فك التشفير
    std::string decrypted = decryptMessage(encrypted, key);

    if (decrypted != originalMessage) {
        std::cerr << "[FAIL] Decrypted text does not match original\n";
        return false;
    }

    return true;
}

int main() {
    int passed = 0, failed = 0;

    if (test_crypto_aes_256_cbc()) {
        std::cout << "[PASS] AES-256-CBC encrypt/decrypt test\n";
        passed++;
    } else {
        std::cout << "[FAIL] AES-256-CBC encrypt/decrypt test\n";
        failed++;
    }

    std::cout << "-----------------------\n";
    std::cout << "Passed: " << passed << "\nFailed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
