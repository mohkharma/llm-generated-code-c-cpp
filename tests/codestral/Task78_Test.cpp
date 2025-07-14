#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <iostream>
#include <string>

// Function to generate RSA private key and return it as a string
std::string generate_rsa_private_key(int bits = 2048) {
    std::string result;
    RSA* rsa = RSA_new();
    BIGNUM* e = BN_new();
    if (!rsa || !e) {
        if (rsa) RSA_free(rsa);
        if (e) BN_free(e);
        return "";
    }
    BN_set_word(e, RSA_F4);
    if (RSA_generate_key_ex(rsa, bits, e, nullptr) != 1) {
        BN_free(e);
        RSA_free(rsa);
        return "";
    }

    BIO* bio = BIO_new(BIO_s_mem());
    if (!bio) {
        BN_free(e);
        RSA_free(rsa);
        return "";
    }

    if (PEM_write_bio_RSAPrivateKey(bio, rsa, nullptr, nullptr, 0, nullptr, nullptr) != 1) {
        BIO_free(bio);
        BN_free(e);
        RSA_free(rsa);
        return "";
    }

    char* data_start = nullptr;
    long data_len = BIO_get_mem_data(bio, &data_start);
    if (data_start && data_len > 0) {
        result.assign(data_start, data_len);
    }

    BIO_free(bio);
    BN_free(e);
    RSA_free(rsa);

    return result;
}

// Simple test runner mimicking "same exact cases"
void run_tests() {
    std::cout << "Running test_generate_rsa_key..." << std::endl;
    std::string key = generate_rsa_private_key();
    if (!key.empty() && key.find("BEGIN RSA PRIVATE KEY") != std::string::npos) {
        std::cout << "test_generate_rsa_key: PASS\n";
    } else {
        std::cout << "test_generate_rsa_key: FAIL\n";
    }
}

int main() {
    run_tests();
    return 0;
}
