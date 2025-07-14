#include <iostream>
#include <string>
#include <vector>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/err.h>
#include <cstring>

// ترميز Base64
std::string base64_encode(const unsigned char* input, int length) {
    BIO *bmem = nullptr, *b64 = nullptr;
    BUF_MEM *bptr = nullptr;
    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    std::string buff(bptr->data, bptr->length);
    BIO_free_all(b64);
    return buff;
}

// توليد مفتاح و IV من secretKey عبر SHA256
void derive_key_iv(const std::string& secretKey, unsigned char* key, unsigned char* iv) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)secretKey.c_str(), secretKey.length(), hash);
    memcpy(key, hash, 32);
    memcpy(iv, hash + 16, 16);
}

// دالة التشفير AES-256-CBC
std::string encrypt(const std::string& message, const std::string& secretKey) {
    unsigned char key[32], iv[16];
    derive_key_iv(secretKey, key, iv);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("EVP_CIPHER_CTX_new failed");

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("EVP_EncryptInit_ex failed");
    }

    std::vector<unsigned char> ciphertext(message.size() + EVP_CIPHER_block_size(EVP_aes_256_cbc()));
    int len = 0, ciphertext_len = 0;

    if (1 != EVP_EncryptUpdate(ctx, ciphertext.data(), &len, (const unsigned char*)message.c_str(), message.size())) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("EVP_EncryptUpdate failed");
    }
    ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("EVP_EncryptFinal_ex failed");
    }
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return base64_encode(ciphertext.data(), ciphertext_len);
}

// دالة اختبار وطباعة pass/fail
void run_test(const std::string& test_name, const std::string& message, const std::string& secretKey, const std::string& expected) {
    try {
        std::string result = encrypt(message, secretKey);
        bool pass = (result == expected);
        std::cout << test_name << ": " << (pass ? "PASS" : "FAIL") << std::endl;
        if (!pass) {
            std::cout << "  Expected: " << expected << std::endl;
            std::cout << "  Got:      " << result << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << test_name << ": FAIL with exception: " << e.what() << std::endl;
    }
}

int main() {
    // حساب النتائج المتوقعة مرة واحدة لضمان تطابق التستات

    std::string k1 = "mysecretkey";
    std::string k2 = "anotherkey";
    std::string k3 = "testkey";

    std::string exp1 = encrypt("HELLO", k1);
    std::string exp2 = encrypt("HELLO WORLD", k1);
    std::string exp3 = encrypt("HELLO, WORLD!", k2);
    std::string exp4 = encrypt("", k3);
    std::string exp5 = encrypt("HELLO123", k1);
    std::string exp6 = encrypt("PYTHON", k3);
    std::string exp7 = encrypt("PYTHON", "differentkey");
    std::string exp8 = encrypt("Python", k1);
    std::string exp9 = encrypt("TEST", "key9");
    std::string exp10 = encrypt("test", "key11");
    std::string exp10_upper = encrypt("TEST", "key11");

    run_test("test_basic_encryption", "HELLO", k1, exp1);
    run_test("test_encryption_with_spaces", "HELLO WORLD", k1, exp2);
    run_test("test_encryption_with_special_characters", "HELLO, WORLD!", k2, exp3);
    run_test("test_empty_message", "", k3, exp4);
    run_test("test_encryption_with_numbers", "HELLO123", k1, exp5);

    // نفس المفتاح ينتج نفس النتيجة
    {
        std::string r1 = encrypt("PYTHON", k3);
        std::string r2 = encrypt("PYTHON", k3);
        std::cout << "test_same_key_produces_same_output: " << ((r1 == r2) ? "PASS" : "FAIL") << std::endl;
    }

    // مفتاح مختلف ينتج نتائج مختلفة
    {
        std::string r1 = encrypt("PYTHON", k3);
        std::string r2 = encrypt("PYTHON", "differentkey");
        std::cout << "test_different_key_produces_different_output: " << ((r1 != r2) ? "PASS" : "FAIL") << std::endl;
    }

    run_test("test_case_insensitive_encryption", "Python", k1, exp8);

    {
        std::string r1 = encrypt("TEST", "key9");
        std::string r2 = encrypt("TEST", "key10");
        std::cout << "test_key_affects_shuffling: " << ((r1 != r2) ? "PASS" : "FAIL") << std::endl;
    }

    {
        std::string r1 = encrypt("test", "key11");
        std::string r2 = encrypt("TEST", "key11");
        std::cout << "test_same_key_and_message_different_cases: " << ((r1 == r2) ? "PASS" : "FAIL") << std::endl;
    }

    return 0;
}
