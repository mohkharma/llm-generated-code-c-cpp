#include <cassert>
#include <iostream>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

// --- الأصلي، لا تغير ---
void secureConnect() {
    const char* server = "https://www.google.com";
    const char* port = "1012";

    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    const SSL_METHOD* method = TLS_client_method();
    SSL_CTX* ctx = SSL_CTX_new(method);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct addrinfo hints, *servinfo;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(server, port, &hints, &servinfo);
    connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);

    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);

    SSL_connect(ssl);

    SSL_free(ssl);
    close(sockfd);
    SSL_CTX_free(ctx);
    EVP_cleanup();
}
// --------------------------

// دالة إنشاء اتصال SSL قابلة لإعادة الاستخدام مع التعامل بالاستثناءات
void create_ssl_connection(const char* server, const char* port) {
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    const SSL_METHOD* method = TLS_client_method();
    SSL_CTX* ctx = SSL_CTX_new(method);
    if (!ctx) throw std::runtime_error("Failed to create SSL_CTX");

    struct addrinfo hints, *servinfo, *p;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int rv = getaddrinfo(server, port, &hints, &servinfo);
    if (rv != 0) {
        SSL_CTX_free(ctx);
        throw std::runtime_error("getaddrinfo failed");
    }

    int sockfd = -1;
    for (p = servinfo; p != NULL; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) continue;

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            sockfd = -1;
            continue;
        }
        break;
    }
    freeaddrinfo(servinfo);

    if (sockfd == -1) {
        SSL_CTX_free(ctx);
        throw std::runtime_error("Failed to connect socket");
    }

    SSL* ssl = SSL_new(ctx);
    if (!ssl) {
        close(sockfd);
        SSL_CTX_free(ctx);
        throw std::runtime_error("Failed to create SSL object");
    }
    SSL_set_fd(ssl, sockfd);

    int ret = SSL_connect(ssl);
    if (ret != 1) {
        SSL_free(ssl);
        close(sockfd);
        SSL_CTX_free(ctx);
        throw std::runtime_error("SSL handshake failed");
    }

    // خيارياً: يمكن إضافة التحقق من الشهادة هنا حسب الحاجة

    SSL_free(ssl);
    close(sockfd);
    SSL_CTX_free(ctx);
    EVP_cleanup();
}

// --- التست كيسز ---

#include <iostream>
#include <exception>

void test_ssl_connection_valid_host() {
    try {
        create_ssl_connection("www.google.com", "443");
        std::cout << "Test Passed: Valid host and port.\n";
    } catch (const std::exception& e) {
        std::cerr << "Test Failed: Error connecting to valid host: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "Test Failed: Unknown error connecting to valid host.\n";
    }
}

void test_ssl_connection_invalid_host() {
    try {
        create_ssl_connection("invalid.host", "443");
        std::cerr << "Test Failed: Expected failure but connection succeeded.\n";
    } catch (...) {
        std::cout << "Test Passed: Invalid host handled correctly.\n";
    }
}

void test_ssl_connection_invalid_port() {
    try {
        create_ssl_connection("www.google.com", "9999");  // Invalid port
        std::cerr << "Test Failed: Expected failure but connection succeeded.\n";
    } catch (...) {
        std::cout << "Test Passed: Invalid port handled correctly.\n";
    }
}

void test_ssl_connection_untrusted_cert() {
    try {
        create_ssl_connection("untrusted-root.badssl.com", "443");
        std::cerr << "Test Failed: Expected failure on untrusted certificate but succeeded.\n";
    } catch (...) {
        std::cout << "Test Passed: Untrusted certificate handled correctly.\n";
    }
}

// وباقي دوال الاختبار تفعل نفس المنطق السابق...

void test_ssl_connection_self_signed_cert() {
    try {
        create_ssl_connection("self-signed.badssl.com", "443");
        std::cerr << "Test Failed: Expected failure on self-signed certificate but succeeded.\n";
    } catch (...) {
        std::cout << "Test Passed: Self-signed certificate handled correctly.\n";
    }
}

void test_ssl_connection_expired_cert() {
    try {
        create_ssl_connection("expired.badssl.com", "443");
        std::cerr << "Test Failed: Expected failure on expired certificate but succeeded.\n";
    } catch (...) {
        std::cout << "Test Passed: Expired certificate handled correctly.\n";
    }
}

void test_ssl_connection_wrong_host_cert() {
    try {
        create_ssl_connection("wrong.host.badssl.com", "443");
        std::cerr << "Test Failed: Expected failure on wrong host certificate but succeeded.\n";
    } catch (...) {
        std::cout << "Test Passed: Certificate for wrong host handled correctly.\n";
    }
}

void test_ssl_connection_revoked_cert() {
    try {
        create_ssl_connection("revoked.badssl.com", "443");
        std::cerr << "Test Failed: Expected failure on revoked certificate but succeeded.\n";
    } catch (...) {
        std::cout << "Test Passed: Revoked certificate handled correctly.\n";
    }
}

void test_ssl_connection_invalid_protocol_version() {
    try {
        create_ssl_connection("www.google.com", "443");
        std::cerr << "Test Failed: Expected failure on invalid protocol version but succeeded.\n";
    } catch (...) {
        std::cout << "Test Passed: Invalid protocol version handled correctly.\n";
    }
}

void test_ssl_connection_successful_reconnect() {
    try {
        create_ssl_connection("www.google.com", "443");
        create_ssl_connection("www.google.com", "443");
        std::cout << "Test Passed: Reconnection successful.\n";
    } catch (const std::exception& e) {
        std::cerr << "Test Failed: Error reconnecting to server: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "Test Failed: Unknown error reconnecting to server.\n";
    }
}


int main() {
    test_ssl_connection_valid_host();
    test_ssl_connection_invalid_host();
    test_ssl_connection_invalid_port();
    test_ssl_connection_untrusted_cert();
    test_ssl_connection_self_signed_cert();
    test_ssl_connection_expired_cert();
    test_ssl_connection_wrong_host_cert();
    test_ssl_connection_revoked_cert();
    test_ssl_connection_invalid_protocol_version();
    test_ssl_connection_successful_reconnect();

    return 0;
}
