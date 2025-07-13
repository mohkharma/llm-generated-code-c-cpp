#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bn.h>
#include "../../../source/output/gpt4o/cpp/Task134_OPENAI_gpt-4o.cpp"

bool test_rsa_key_save_load() {
    // توليد مفتاح RSA جديد (يفضل استخدام EVP_PKEY_new من API الحديثة، لكن نستخدم هنا RSA_generate_key_ex)
    RSA* rsa = RSA_new();
    BIGNUM* e = BN_new();
    BN_set_word(e, RSA_F4);

    if (RSA_generate_key_ex(rsa, 2048, e, nullptr) != 1) {
        std::cerr << "[FAIL] RSA key generation failed\n";
        BN_free(e);
        RSA_free(rsa);
        return false;
    }
    BN_free(e);

    const char* filename = "private_key.pem";

    // حفظ المفتاح
    save_key(rsa, filename);

    // تحميل المفتاح
    RSA* loaded_rsa = load_key(filename);
    if (!loaded_rsa) {
        std::cerr << "[FAIL] RSA key loading failed\n";
        RSA_free(rsa);
        return false;
    }

    // الوصول إلى مكونات المفتاح باستخدام الدالة RSA_get0_key
    const BIGNUM *n = nullptr, *e_bn = nullptr, *d = nullptr;
    RSA_get0_key(loaded_rsa, &n, &e_bn, &d);

    if (n == nullptr || e_bn == nullptr) {
        std::cerr << "[FAIL] Loaded RSA key components are null\n";
        RSA_free(rsa);
        RSA_free(loaded_rsa);
        return false;
    }

    // تحويل المكون n إلى نص هكس
    char* n_hex = BN_bn2hex(n);
    if (!n_hex) {
        std::cerr << "[FAIL] Failed to convert RSA key component to hex\n";
        RSA_free(rsa);
        RSA_free(loaded_rsa);
        return false;
    }

    std::cout << "RSA modulus n (hex): " << n_hex << std::endl;
    OPENSSL_free(n_hex);

    RSA_free(rsa);
    RSA_free(loaded_rsa);

    return true;
}

int main() {
    int passed = 0, failed = 0;

    if (test_rsa_key_save_load()) {
        std::cout << "[PASS] RSA key save/load test\n";
        passed++;
    } else {
        std::cout << "[FAIL] RSA key save/load test\n";
        failed++;
    }

    std::cout << "-----------------------\n";
    std::cout << "Passed: " << passed << "\nFailed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
