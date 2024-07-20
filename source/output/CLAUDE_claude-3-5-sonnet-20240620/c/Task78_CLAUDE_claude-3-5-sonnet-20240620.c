
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

int main() {
    RSA *rsa = RSA_new();
    BIGNUM *bne = BN_new();
    BN_set_word(bne, RSA_F4);

    RSA_generate_key_ex(rsa, 2048, bne, NULL);

    BIO *bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);

    char *pem_key;
    long pem_size = BIO_get_mem_data(bio, &pem_key);

    printf("-----BEGIN OPENSSH PRIVATE KEY-----\
");
    BIO_dump_fp(stdout, pem_key, pem_size);
    printf("-----END OPENSSH PRIVATE KEY-----\
");

    BIO_free_all(bio);
    RSA_free(rsa);
    BN_free(bne);

    return 0;
}
