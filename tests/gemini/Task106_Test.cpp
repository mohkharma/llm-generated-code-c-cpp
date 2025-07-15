#include <iostream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

using namespace std;

// Generate RSA key pair
void generateKeys(RSA* &rsa) {
  BIGNUM *bne = BN_new();
  BN_set_word(bne, RSA_F4);

  rsa = RSA_new();
  RSA_generate_key_ex(rsa, 2048, bne, NULL);
  BN_free(bne);
}

// Encrypt message
string encrypt(const string &message, RSA *rsa) {
  int encryptedLength = RSA_size(rsa);
  unsigned char *encrypted = new unsigned char[encryptedLength];
  int length = RSA_public_encrypt(message.length(),
                                 (const unsigned char*)message.c_str(),
                                 encrypted,
                                 rsa,
                                 RSA_PKCS1_OAEP_PADDING);
  if (length == -1) {
    cerr << "Error encrypting message: " << ERR_error_string(ERR_get_error(), NULL) << endl;
    delete[] encrypted;
    return "";
  }
  string encryptedMessage((char*)encrypted, length);
  delete[] encrypted;
  return encryptedMessage;
}

// Decrypt message
string decrypt(const string &encryptedMessage, RSA *rsa) {
  int decryptedLength = RSA_size(rsa);
  unsigned char *decrypted = new unsigned char[decryptedLength];
  int length = RSA_private_decrypt(encryptedMessage.length(),
                                  (const unsigned char*)encryptedMessage.c_str(),
                                  decrypted,
                                  rsa,
                                  RSA_PKCS1_OAEP_PADDING);
  if (length == -1) {
    cerr << "Error decrypting message: " << ERR_error_string(ERR_get_error(), NULL) << endl;
    delete[] decrypted;
    return "";
  }
  string decryptedMessage((char*)decrypted, length);
  delete[] decrypted;
  return decryptedMessage;
}

int main() {
  RSA *rsa = nullptr;
  generateKeys(rsa);

  // Test messages (same as Python cases)
  string testMessages[] = {
    "HELLO",
    "WORLD",
    "TEST123",
    "RSA_ENCRYPTION",
    ""  // empty string test
  };

  for (const auto& message : testMessages) {
    string encryptedMessage = encrypt(message, rsa);
    string decryptedMessage = decrypt(encryptedMessage, rsa);

    cout << "Original Message: \"" << message << "\"" << endl;
    cout << "Decrypted Message: \"" << decryptedMessage << "\"" << endl;
    if (decryptedMessage == message) {
      cout << "Result: PASS\n" << endl;
    } else {
      cout << "Result: FAIL\n" << endl;
    }
  }

  RSA_free(rsa);
  return 0;
}
