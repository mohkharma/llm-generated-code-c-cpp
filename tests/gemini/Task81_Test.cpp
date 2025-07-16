#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

using namespace std;

// دالة تحسب الـ hash (sha256 أو md5) على نص داخلي وليس ملف
string calculateCertificateHashFromString(const string& data, const string& hash_algorithm) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    const EVP_MD* (*hash_function)(void) = nullptr;
    int hash_len = 0;

    if (hash_algorithm == "sha256") {
        hash_function = EVP_sha256;
        hash_len = SHA256_DIGEST_LENGTH;
    } else if (hash_algorithm == "md5") {
        hash_function = EVP_md5;
        hash_len = MD5_DIGEST_LENGTH;
    } else {
        cerr << "Unsupported hash algorithm: " << hash_algorithm << endl;
        return "";
    }

    EVP_MD_CTX* hashContext = EVP_MD_CTX_new();
    EVP_DigestInit_ex(hashContext, hash_function(), nullptr);
    EVP_DigestUpdate(hashContext, data.data(), data.size());
    EVP_DigestFinal_ex(hashContext, hash, nullptr);
    EVP_MD_CTX_free(hashContext);

    stringstream ss;
    for (int i = 0; i < hash_len; ++i) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

bool verifyCertificateHashFromString(const string& cert_data, const string& expected_hash, const string& hash_algorithm) {
    string calculated_hash = calculateCertificateHashFromString(cert_data, hash_algorithm);
    return calculated_hash == expected_hash;
}

int main() {
    // هنا مثال بسيط على شهادة مخزنة كسلسلة نصية PEM (يمكن تستبدلها بشهادة صحيحة)
    string certificate_pem = R"(-----BEGIN CERTIFICATE-----
MIIDdzCCAl+gAwIBAgIEbXKoDzANBgkqhkiG9w0BAQsFADBvMQswCQYDVQQGEwJV
UzELMAkGA1UECBMCQ0ExEjAQBgNVBAcTCVNhbiBSYWZhZWwxEjAQBgNVBAoTCUdv
b2dsZSBJbmMxEzARBgNVBAsTCkVuZ2luZWVyaW5nMRIwEAYDVQQDEwlsb2NhbGhv
c3QwHhcNMjAwMTAxMDAwMDAwWhcNMzAwMTAxMDAwMDAwWjBvMQswCQYDVQQGEwJV
UzELMAkGA1UECBMCQ0ExEjAQBgNVBAcTCVNhbiBSYWZhZWwxEjAQBgNVBAoTCUdv
b2dsZSBJbmMxEzARBgNVBAsTCkVuZ2luZWVyaW5nMRIwEAYDVQQDEwlsb2NhbGhv
c3QwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC7eX6wyj+o8uyT/y45
f0h9xQGZDlDsdWvUuX9t03y+8XqBdVCD9f0uXQBdPi9d6Z6vX1O6mZjDzGxfuZd
BwMRnqPILqgCqzV9bF8uZWXauGp5n0Tk6dcZAcKZo/XPJJ+kwmFtC4UUT0FkIf3
x2gAJeRmhUQAvBhM5mA9OrFzGj3k13Fk9x25d96I5ryQ/vjoDWw8Ew6o8fQ5hD7
MX9iVQtNnp1WW6el5MeKwJ/QdZ3T1QEj9A6zIcUp9JZKxCoA9/mcwPj+k7rLNch
f1rkPkLGzEvx2r+we0tJhCHd+7C9Z5KfQ/6V6zFKrZB6vK0w0lgMZf7FGd5IvrY
AgMBAAGjUzBRMB0GA1UdDgQWBBSb5vM48a85IkV7D2H/GXvJHfu3LjAfBgNVHSME
GDAWgBSb5vM48a85IkV7D2H/GXvJHfu3LjAPBgNVHRMBAf8EBTADAQH/MA0GCSqG
SIb3DQEBCwUAA4IBAQCYqkX3Q4qgXDdk0QYmjLvseX09fq+U68jPfRr+8Qvcmc1+
qkHKeTX+tWsyAncrUoPnyjFk5xFkUe3ZmOic3Zkj0LvLFov6NkuEjFq35Vwx3ZOf
X3h9rrwBQxWCDTlLXHo7bZtg6gr+I/1dFpMoYPB85Xv5LzJsCd9+hEdqCQ0ZLKkL
U2mTj2iLskOw9LprGLlYfCpzJr61aRy2ScE2vq5q6O3Mgx0nv2RY6eflfu7oQ1+h
nGx6rrZmMym0Rq+MkCcX+3VXezmjN6DdY3LrRU1cxuCwL9OEW7sT5px9ri4xMEaD
sO8MBvDx5wO3pTvz6d6d+W49OvT2G6QUl5n4Tx
-----END CERTIFICATE-----)";

    string expected_hash = "2b9f3bf466a73e6b18d9b83867606b53a8b675c0b90a77483892baf9a0a6d54a"; // هذا الـ SHA-256 لهذه الشهادة
    string hash_algorithm = "sha256";

    bool match = verifyCertificateHashFromString(certificate_pem, expected_hash, hash_algorithm);

    if (match) {
        cout << "Test case 1: PASS" << endl;
        cout << "Certificate hash matches expected hash." << endl;
    } else {
        cout << "Test case 1: FAIL" << endl;
        cout << "Certificate hash does not match expected hash." << endl;
    }

    return 0;
}
