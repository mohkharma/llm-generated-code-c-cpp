#include <iostream>
#include <string>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <cstring>
#include <cstdio>

void encryptAndPrintHex(const std::string& plainText, const std::string& keyStr) {
    unsigned char iv[AES_BLOCK_SIZE] = {0};

    unsigned char key[16];  // 128-bit key
    std::memset(key, 0, sizeof(key));
    std::memcpy(key, keyStr.c_str(), std::min(keyStr.size(), sizeof(key)));

    AES_KEY aes_key;
    if (AES_set_encrypt_key(key, 128, &aes_key) != 0) {
        std::cerr << "Failed to set AES encryption key." << std::endl;
        return;
    }

    int len = plainText.length();
    int blockSize = AES_BLOCK_SIZE;
    int padding = blockSize - (len % blockSize);
    int totalLen = len + padding;

    unsigned char* paddedInput = new unsigned char[totalLen];
    std::memcpy(paddedInput, plainText.c_str(), plainText.length());
    for (int i = 0; i < padding; ++i) {
        paddedInput[plainText.length() + i] = static_cast<unsigned char>(padding);
    }

    unsigned char* encryptedData = new unsigned char[totalLen];
    AES_cbc_encrypt(paddedInput, encryptedData, totalLen, &aes_key, iv, AES_ENCRYPT);

    for (int i = 0; i < totalLen; ++i) {
        printf("%02x", encryptedData[i]);
    }
    std::cout << std::endl;

    delete[] paddedInput;
    delete[] encryptedData;
}
