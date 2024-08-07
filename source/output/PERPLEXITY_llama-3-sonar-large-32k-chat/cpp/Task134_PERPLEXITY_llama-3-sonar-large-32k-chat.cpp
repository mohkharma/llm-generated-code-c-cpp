#include <iostream>
#include <map>
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

class KeyManager {
private:
    std::map<std::string, RSA*> keys;

public:
    KeyManager() {}

    void generateKey(const std::string& keyName) {
        RSA* key = RSA_new();
        BIGNUM* exponent = BN_new();
        BN_set_word(exponent, 65537);
        RSA_generate_key_ex(key, 2048, exponent, nullptr);
        this->keys[keyName] = key;
    }

    RSA* getKey(const std::string& keyName) {
        return this->keys[keyName];
    }

    void deleteKey(const std::string& keyName) {
        if (this->keys.find(keyName) != this->keys.end()) {
            RSA_free(this->keys[keyName]);
            this->keys.erase(keyName);
        }
    }

    std::string hashKey(const std::string& keyName) {
        RSA* key = this->getKey(keyName);
        if (key != nullptr) {
            unsigned char* buffer = nullptr;
//error: ‘i2s_PublicKey’ was not declared in this scope; did you mean ‘i2d_PublicKey’?
            //fixed by regeneration
            int length = i2d_RSAPublicKey(key, &buffer);
            std::string keyString((char*)buffer, length);
            OPENSSL_free(buffer);
            unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256((unsigned char*)keyString.c_str(), keyString.length(), hash);
            std::string hashString((char*)hash, SHA256_DIGEST_LENGTH);
            return hashString;
        } else {
            return "";
        }
    }
};

int main() {
    KeyManager manager;
    std::string keyName = "my_key";
    manager.generateKey(keyName);
    RSA* key = manager.getKey(keyName);
    std::cout << "Generated key for " << keyName << ": ";
    unsigned char* buffer = nullptr;
    int length = i2d_RSAPublicKey(key, &buffer);
    std::cout << std::string((char*)buffer, length) << std::endl;
    OPENSSL_free(buffer);
    std::cout << "Hash of " << keyName << ": " << manager.hashKey(keyName) << std::endl;
    manager.deleteKey(keyName);
    std::cout << "Key " << keyName << " deleted: ";
    if (manager.getKey(keyName) == nullptr) {
        std::cout << "null" << std::endl;
    } else {
        std::cout << "not null" << std::endl;
    }
    return 0;
}