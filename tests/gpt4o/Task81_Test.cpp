#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <openssl/sha.h>
#include <openssl/x509.h>
#include <openssl/pem.h>

std::string get_cert_hash_from_string(const std::string& cert_pem) {
    BIO *bio = BIO_new_mem_buf(cert_pem.data(), (int)cert_pem.size());
    if (!bio) throw std::runtime_error("Failed to create BIO");

    X509 *cert = PEM_read_bio_X509(bio, NULL, 0, NULL);
    if (!cert) {
        BIO_free(bio);
        throw std::runtime_error("Failed to parse certificate");
    }

    unsigned char *der = NULL;
    int len = i2d_X509(cert, &der);
    if (len < 0) {
        X509_free(cert);
        BIO_free(bio);
        throw std::runtime_error("Failed to convert cert to DER");
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(der, len, hash);

    OPENSSL_free(der);
    X509_free(cert);
    BIO_free(bio);

    std::ostringstream oss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return oss.str();
}

int main() {
    // مثال شهادة PEM مخزنة داخلياً (استبدلها بشهادة فعلية إذا تريد)
    const std::string cert_pem =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIDdzCCAl+gAwIBAgIEbXKoDzANBgkqhkiG9w0BAQsFADBvMQswCQYDVQQGEwJV\n"
    "UzELMAkGA1UECBMCQ0ExEjAQBgNVBAcTCVNhbiBSYWZhZWwxEjAQBgNVBAoTCUdv\n"
    "b2dsZSBJbmMxEzARBgNVBAsTCkVuZ2luZWVyaW5nMRIwEAYDVQQDEwlsb2NhbGhv\n"
    "c3QwHhcNMjAwMTAxMDAwMDAwWhcNMzAwMTAxMDAwMDAwWjBvMQswCQYDVQQGEwJV\n"
    "UzELMAkGA1UECBMCQ0ExEjAQBgNVBAcTCVNhbiBSYWZhZWwxEjAQBgNVBAoTCUdv\n"
    "b2dsZSBJbmMxEzARBgNVBAsTCkVuZ2luZWVyaW5nMRIwEAYDVQQDEwlsb2NhbGhv\n"
    "c3QwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC7eX6wyj+o8uyT/y45\n"
    "f0h9xQGZDlDsdWvUuX9t03y+8XqBdVCD9f0uXQBdPi9d6Z6vX1O6mZjDzGxfuZd\n"
    "BwMRnqPILqgCqzV9bF8uZWXauGp5n0Tk6dcZAcKZo/XPJJ+kwmFtC4UUT0FkIf3\n"
    "x2gAJeRmhUQAvBhM5mA9OrFzGj3k13Fk9x25d96I5ryQ/vjoDWw8Ew6o8fQ5hD7\n"
    "MX9iVQtNnp1WW6el5MeKwJ/QdZ3T1QEj9A6zIcUp9JZKxCoA9/mcwPj+k7rLNch\n"
    "f1rkPkLGzEvx2r+we0tJhCHd+7C9Z5KfQ/6V6zFKrZB6vK0w0lgMZf7FGd5IvrY\n"
    "AgMBAAGjUzBRMB0GA1UdDgQWBBSb5vM48a85IkV7D2H/GXvJHfu3LjAfBgNVHSME\n"
    "GDAWgBSb5vM48a85IkV7D2H/GXvJHfu3LjAPBgNVHRMBAf8EBTADAQH/MA0GCSqG\n"
    "SIb3DQEBCwUAA4IBAQCYqkX3Q4qgXDdk0QYmjLvseX09fq+U68jPfRr+8Qvcmc1+\n"
    "qkHKeTX+tWsyAncrUoPnyjFk5xFkUe3ZmOic3Zkj0LvLFov6NkuEjFq35Vwx3ZOf\n"
    "X3h9rrwBQxWCDTlLXHo7bZtg6gr+I/1dFpMoYPB85Xv5LzJsCd9+hEdqCQ0ZLKkL\n"
    "U2mTj2iLskOw9LprGLlYfCpzJr61aRy2ScE2vq5q6O3Mgx0nv2RY6eflfu7oQ1+h\n"
    "nGx6rrZmMym0Rq+MkCcX+3VXezmjN6DdY3LrRU1cxuCwL9OEW7sT5px9ri4xMEaD\n"
    "sO8MBvDx5wO3pTvz6d6d+W49OvT2G6QUl5n4Tx\n"
    "-----END CERTIFICATE-----\n";

    const std::string expected_hash = "2b9f3bf466a73e6b18d9b83867606b53a8b675c0b90a77483892baf9a0a6d54a"; // هذا الـ SHA256 لهذه الشهادة

    try {
        std::string calculated_hash = get_cert_hash_from_string(cert_pem);

        if (calculated_hash == expected_hash) {
            std::cout << "Test case 1: PASS" << std::endl;
            std::cout << "Certificate hash matches expected hash." << std::endl;
        } else {
            std::cout << "Test case 1: FAIL" << std::endl;
            std::cout << "Certificate hash does not match expected hash." << std::endl;
            std::cout << "Calculated hash: " << calculated_hash << std::endl;
            std::cout << "Expected hash:   " << expected_hash << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Test case 1: FAIL" << std::endl;
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
