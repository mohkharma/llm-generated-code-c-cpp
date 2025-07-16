#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <string.h>
#include <vector>

void handleErrors(const char* msg) {
    char err[130];
    ERR_load_crypto_strings();
    ERR_error_string(ERR_get_error(), err);
    std::cerr << msg << ": " << err << std::endl;
}

int main() {
    int bits = 2048;
    unsigned long e = RSA_F4;
    RSA *rsa = RSA_generate_key(bits, e, NULL, NULL);

    BIO *pri = BIO_new(BIO_s_mem());
    BIO *pub = BIO_new(BIO_s_mem());

    PEM_write_bio_RSAPrivateKey(pri, rsa, NULL, NULL, 0, NULL, NULL);
    PEM_write_bio_RSAPublicKey(pub, rsa);

    size_t pri_len = BIO_pending(pri);
    size_t pub_len = BIO_pending(pub);

    char *pri_key = (char*)malloc(pri_len + 1);
    char *pub_key = (char*)malloc(pub_len + 1);

    BIO_read(pri, pri_key, pri_len);
    BIO_read(pub, pub_key, pub_len);

    pri_key[pri_len] = '\0';
    pub_key[pub_len] = '\0';

    // Load public key from PEM string
    RSA *rsa_public = RSA_new();
    BIO *pubbio = BIO_new_mem_buf(pub_key, -1);
    PEM_read_bio_RSAPublicKey(pubbio, &rsa_public, NULL, NULL);

    // Load private key from PEM string
    RSA *rsa_private = RSA_new();
    BIO *pribio = BIO_new_mem_buf(pri_key, -1);
    PEM_read_bio_RSAPrivateKey(pribio, &rsa_private, NULL, NULL);

    // Test messages (same as Python tests)
    std::vector<std::string> test_messages = {
        "HELLO",
        "WORLD",
        "TEST123",
        "RSA_ENCRYPTION",
        ""  // empty string test
    };

    for (const auto& message : test_messages) {
        int encrypted_length = RSA_size(rsa_public);
        char *encrypted = (char*)malloc(encrypted_length);

        int enc_len = RSA_public_encrypt(message.length(),
                                         (unsigned char*)message.c_str(),
                                         (unsigned char*)encrypted,
                                         rsa_public,
                                         RSA_PKCS1_OAEP_PADDING);
        if(enc_len == -1) {
            handleErrors("Encryption Error");
            free(encrypted);
            std::cout << "Test message: \"" << message << "\"\nResult: FAIL\n\n";
            continue;
        }

        char *decrypted = (char*)malloc(enc_len);
        int dec_len = RSA_private_decrypt(enc_len,
                                         (unsigned char*)encrypted,
                                         (unsigned char*)decrypted,
                                         rsa_private,
                                         RSA_PKCS1_OAEP_PADDING);
        if(dec_len == -1) {
            handleErrors("Decryption Error");
            free(encrypted);
            free(decrypted);
            std::cout << "Test message: \"" << message << "\"\nResult: FAIL\n\n";
            continue;
        }

        std::string decrypted_str(decrypted, dec_len);

        std::cout << "Test message: \"" << message << "\"\n";
        std::cout << "Decrypted message: \"" << decrypted_str << "\"\n";

        if (decrypted_str == message) {
            std::cout << "Result: PASS\n\n";
        } else {
            std::cout << "Result: FAIL\n\n";
        }

        free(encrypted);
        free(decrypted);
    }

    RSA_free(rsa);
    RSA_free(rsa_public);
    RSA_free(rsa_private);
    BIO_free_all(pri);
    BIO_free_all(pub);
    BIO_free_all(pubbio);
    BIO_free_all(pribio);
    free(pri_key);
    free(pub_key);

    return 0;
}
