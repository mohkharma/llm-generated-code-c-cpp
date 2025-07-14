#include <iostream>
#include <string>
#include <openssl/aes.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <cstdio>

std::string encryptAESCBC(unsigned char* key, const std::string& plaintext) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    unsigned char iv[AES_BLOCK_SIZE];
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        iv[i] = 0;
    }
    int len = plaintext.length();
    // AES_cbc_encrypt requires input length multiple of AES_BLOCK_SIZE
    // We need to pad plaintext accordingly (PKCS7)
    int padded_len = ((len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* input = new unsigned char[padded_len];
    memcpy(input, plaintext.c_str(), len);
    // PKCS7 padding
    unsigned char pad_val = padded_len - len;
    for (int i = len; i < padded_len; i++) {
        input[i] = pad_val;
    }

    unsigned char* encrypted = new unsigned char[padded_len];
    AES_cbc_encrypt(input, encrypted, padded_len, &aes_key, iv, AES_ENCRYPT);

    std::string encrypted_str((char*)encrypted, padded_len);

    delete[] input;
    delete[] encrypted;
    return encrypted_str;
}

int main() {
    unsigned char key[16];
    // Fill key with fixed data (e.g., all 0x01) for repeatable test
    memset(key, 0x01, sizeof(key));

    std::string plaintext = "MySecretKey123456";

    std::string encrypted = encryptAESCBC(key, plaintext);

    std::cout << "Test case 1: Encrypting \"" << plaintext << "\" with fixed key\n";

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
