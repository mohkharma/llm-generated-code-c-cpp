// #include <iostream>
// #include <fstream>
// #include <openssl/rsa.h>
// #include <openssl/pem.h>
//
// void save_key(RSA* key, const char* filename) {
//     FILE* file = fopen(filename, "wb");
//     PEM_write_RSAPrivateKey(file, key, nullptr, nullptr, 0, nullptr, nullptr);
//     fclose(file);
// }
//
// RSA* load_key(const char* filename) {
//     RSA* rsa = RSA_new();
//     FILE* file = fopen(filename, "rb");
//     PEM_read_RSAPrivateKey(file, &rsa, nullptr, nullptr);
//     fclose(file);
//     return rsa;
// }
//
// int main() {
//     RSA* rsa = RSA_generate_key(2048, RSA_F4, nullptr, nullptr);
//     save_key(rsa, "private_key.pem");
//     RSA* loaded_rsa = load_key("private_key.pem");
//     //error: invalid use of incomplete type ‘RSA’ {aka ‘struct rsa_st’}
//     char* key_str = BN_bn2hex(loaded_rsa->p);
//     std::cout << "Key: " << key_str << std::endl;
//     OPENSSL_free(key_str);
//     RSA_free(rsa);
//     RSA_free(loaded_rsa);
//     return 0;
// }


#include <iostream>
#include <fstream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bn.h>

void save_key(RSA* key, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file) {
        PEM_write_RSAPrivateKey(file, key, nullptr, nullptr, 0, nullptr, nullptr);
        fclose(file);
    }
}

RSA* load_key(const char* filename) {
    RSA* rsa = RSA_new();
    FILE* file = fopen(filename, "rb");
    if (file) {
        PEM_read_RSAPrivateKey(file, &rsa, nullptr, nullptr);
        fclose(file);
    }
    return rsa;
}

int main() {
    RSA* rsa = RSA_generate_key(2048, RSA_F4, nullptr, nullptr);
    save_key(rsa, "private_key.pem");

    RSA* loaded_rsa = load_key("private_key.pem");

    const BIGNUM* p = nullptr;
    RSA_get0_factors(loaded_rsa, &p, nullptr);

    if (p) {
        char* key_str = BN_bn2hex(p);
        std::cout << "Key: " << key_str << std::endl;
        OPENSSL_free(key_str);
    } else {
        std::cerr << "Failed to retrieve RSA factor p." << std::endl;
    }

    RSA_free(rsa);
    RSA_free(loaded_rsa);
    return 0;
}
