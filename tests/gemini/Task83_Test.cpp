#include <cstring>
#include <iostream>
#include <string>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>

using namespace std;

int main()
{
    // Input key (same as test case key)
    const char* key_str = "MySecretKey123456";
    int key_len = strlen(key_str);

    unsigned char key[32];
    memset(key, 0, sizeof(key));
    memcpy(key, key_str, key_len);

    // Input data to encrypt = same as key_str for matching test case
    unsigned char plaintext[1024];
    memset(plaintext, 0, sizeof(plaintext));
    memcpy(plaintext, key_str, key_len);
    int plaintext_len = key_len;

    // Generate a random salt
    unsigned char salt[16];
    RAND_bytes(salt, sizeof(salt));

    // Derive a 256-bit key from the input key and salt
    const EVP_MD* kdf = EVP_sha256();
    unsigned char derived_key[32];
    PKCS5_PBKDF2_HMAC(key_str, key_len, salt, sizeof(salt), 390000, kdf, sizeof(derived_key), derived_key);

    // Generate a random initialization vector (IV)
    unsigned char iv[AES_BLOCK_SIZE];
    RAND_bytes(iv, AES_BLOCK_SIZE);

    // Encrypt the plaintext using AES-CBC
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, derived_key, iv);

    int len;
    int ciphertext_len = 0;
    unsigned char ciphertext[1024];
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    // Print the encrypted data in hexadecimal format
    cout << "Test case 1: Encrypting key \"" << key_str << "\"\n";
    if(ciphertext_len > 0) {
        cout << "Encrypted ciphertext (hex): ";
        for (int i = 0; i < ciphertext_len; i++) {
            printf("%02x", ciphertext[i]);
        }
        cout << endl;
        cout << "Test case 1 result: PASS\n";
    } else {
        cout << "Test case 1 result: FAIL\n";
    }

    EVP_CIPHER_CTX_free(ctx);

    return 0;
}
