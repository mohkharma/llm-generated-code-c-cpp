#include <iostream>
#include <string>
#include <vector>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>

std::vector<unsigned char> encrypt(const std::vector<unsigned char>& key, const std::vector<unsigned char>& plaintext) {
    std::vector<unsigned char> ciphertext(plaintext.size() + AES_BLOCK_SIZE);
    unsigned char iv[AES_BLOCK_SIZE];
    RAND_bytes(iv, AES_BLOCK_SIZE);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key.data(), iv);

    int len;
    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(), plaintext.size());
    int ciphertext_len = len;

    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    ciphertext.resize(ciphertext_len);
    ciphertext.insert(ciphertext.begin(), iv, iv + AES_BLOCK_SIZE);

    return ciphertext;
}

int main() {
    // Test case 1: Use fixed key of 16 bytes = 0x01 to 0x10 (for reproducibility)
    std::vector<unsigned char> key(16);
    for (int i = 0; i < 16; i++) key[i] = static_cast<unsigned char>(i + 1);

    // Encrypt the string "MySecretKey123456" (same as python test case)
    std::string plaintext_str = "MySecretKey123456";
    std::vector<unsigned char> plaintext(plaintext_str.begin(), plaintext_str.end());

    std::vector<unsigned char> encrypted = encrypt(key, plaintext);

    std::cout << "Test case 1: Encrypting \"" << plaintext_str << "\" with fixed key\n";

    if (!encrypted.empty()) {
        std::cout << "Encrypted data (hex): ";
        for (unsigned char c : encrypted) {
            printf("%02x", c);
        }
        std::cout << std::endl;
        std::cout << "Test case 1 result: PASS\n";
    } else {
        std::cout << "Test case 1 result: FAIL\n";
    }

    return 0;
}
