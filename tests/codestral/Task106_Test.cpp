#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// Encrypt data with public key
std::vector<unsigned char> rsa_encrypt(RSA* rsa, const std::string& data) {
    std::vector<unsigned char> encrypted(RSA_size(rsa));
    int len = RSA_public_encrypt(data.size(),
                                 reinterpret_cast<const unsigned char*>(data.c_str()),
                                 encrypted.data(),
                                 rsa,
                                 RSA_PKCS1_PADDING);
    if (len == -1) {
        ERR_print_errors_fp(stderr);
        return {};
    }
    encrypted.resize(len);
    return encrypted;
}

// Decrypt data with private key
std::string rsa_decrypt(RSA* rsa, const std::vector<unsigned char>& encrypted) {
    std::vector<unsigned char> decrypted(RSA_size(rsa));
    int len = RSA_private_decrypt(encrypted.size(),
                                  encrypted.data(),
                                  decrypted.data(),
                                  rsa,
                                  RSA_PKCS1_PADDING);
    if (len == -1) {
        ERR_print_errors_fp(stderr);
        return "";
    }
    return std::string(reinterpret_cast<char*>(decrypted.data()), len);
}

int main() {
    // Initialize OpenSSL error strings (optional but helpful)
    ERR_load_crypto_strings();

    // Generate RSA keypair
    RSA* rsa = RSA_new();
    BIGNUM* e = BN_new();
    BN_set_word(e, RSA_F4);
    if (!RSA_generate_key_ex(rsa, 2048, e, nullptr)) {
        std::cerr << "RSA key generation failed." << std::endl;
        ERR_print_errors_fp(stderr);
        return 1;
    }

    BN_free(e);

    // Test cases (same messages as your Python tests)
    std::vector<std::string> test_messages = {
        "HELLO",
        "WORLD",
        "TEST123",
        "RSA_ENCRYPTION",
        ""  // empty string test
    };

    for (const auto& message : test_messages) {
        auto encrypted = rsa_encrypt(rsa, message);
        if (encrypted.empty()) {
            std::cout << "Encryption failed for message: \"" << message << "\"\n";
            std::cout << "Result: FAIL\n\n";
            continue;
        }

        auto decrypted = rsa_decrypt(rsa, encrypted);

        std::cout << "Original message: \"" << message << "\"\n";
        std::cout << "Decrypted message: \"" << decrypted << "\"\n";

        if (decrypted == message) {
            std::cout << "Result: PASS\n\n";
        } else {
            std::cout << "Result: FAIL\n\n";
        }
    }

    RSA_free(rsa);
    ERR_free_strings();

    return 0;
}
