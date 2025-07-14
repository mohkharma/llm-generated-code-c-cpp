#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <openssl/rsa.h>
#include <openssl/pem.h>
// نستخدم دالة generate_rsa_key() من الكود الأصلي بالربط أو تعريفها مباشرة في هذا الملف

std::string generate_rsa_key() {
    RSA *rsa = RSA_new();
    BIGNUM *bne = BN_new();
    BN_set_word(bne, RSA_F4);
    RSA_generate_key_ex(rsa, 2048, bne, NULL);

    BIO *bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);

    char *pem_key;
    long pem_size = BIO_get_mem_data(bio, &pem_key);
    std::string ssh_key(pem_key, pem_size);

    BIO_free_all(bio);
    RSA_free(rsa);
    BN_free(bne);

    return ssh_key;
}
void run_test() {
    std::string key = generate_rsa_key();

    // نتحقق إذا المفتاح يبدأ بـ BEGIN RSA PRIVATE KEY
    if (key.find("-----BEGIN RSA PRIVATE KEY-----") == 0) {
        std::cout << "test_generate_rsa_key: PASS\n";
    } else {
        std::cout << "test_generate_rsa_key: FAIL\n";
    }
}

int main() {
    run_test();
    return 0;
}
