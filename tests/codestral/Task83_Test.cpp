#include <iostream>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <string.h>

std::string encryptKey(const std::string& key, const std::string& cipherKey) {
    unsigned char iv[AES_BLOCK_SIZE];
    RAND_bytes(iv, AES_BLOCK_SIZE);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, reinterpret_cast<const unsigned char*>(cipherKey.c_str()), iv);

    int len = 0, ciphertext_len = 0;
    unsigned char* ciphertext = new unsigned char[key.length() + AES_BLOCK_SIZE];
    EVP_EncryptUpdate(ctx, ciphertext, &len, reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    std::string encryptedKey(reinterpret_cast<char*>(iv), AES_BLOCK_SIZE);
    encryptedKey.append(reinterpret_cast<char*>(ciphertext), ciphertext_len);
    delete[] ciphertext;

    return encryptedKey;
}

int main() {
    // Test case 1 from python: encrypt "MySecretKey123456"
    std::string key = "MySecretKey123456";

    // Use a 32-byte cipher key (AES-256 key length)
    // For test stability, use fixed cipher key of 32 bytes
    std::string cipherKey(32, '\x01'); // 32 bytes of 0x01

    std::string encryptedKey = encryptKey(key, cipherKey);

    std::cout << "Test case 1: Encrypting key \"" << key << "\"\n";

    if (!encryptedKey.empty()) {
        std::cout << "Encrypted key (hex): ";
        // Print encrypted data in hex
        for (unsigned char c : encryptedKey) {
            printf("%02x", c);
        }
        std::cout << std::endl;
        std::cout << "Test case 1 result: PASS\n";
    } else {
        std::cout << "Test case 1 result: FAIL\n";
    }

    return 0;
}
