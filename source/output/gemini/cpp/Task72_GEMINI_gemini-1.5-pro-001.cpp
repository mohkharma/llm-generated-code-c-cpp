#include <iostream>
#include <string>
#include <vector>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>

using namespace std;

// Function to handle encryption errors
void handleErrors(void) {
  ERR_print_errors_fp(stderr);
  abort();
}

// Function to encrypt data using AES-CBC with a static IV
vector<unsigned char> encryptData(const unsigned char *plaintext, int plaintext_len,
                                  const unsigned char *key, const unsigned char *iv) {
  // Create and initialize cipher context
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  if (!ctx) handleErrors();

  // Set cipher to AES-CBC
  if (EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv) != 1)
    handleErrors();

  // Output buffer for encrypted data
  vector<unsigned char> ciphertext(plaintext_len + AES_BLOCK_SIZE);
  int len;

  // Encrypt the plaintext
  if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext, plaintext_len) != 1)
    handleErrors();
  int ciphertext_len = len;

  // Finalize encryption
  if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len) != 1)
    handleErrors();
  ciphertext_len += len;

  // Resize ciphertext vector to actual size
  ciphertext.resize(ciphertext_len);

  // Clean up and return ciphertext
  EVP_CIPHER_CTX_free(ctx);
  return ciphertext;
}
