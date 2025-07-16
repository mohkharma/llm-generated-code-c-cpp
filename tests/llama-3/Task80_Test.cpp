#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <arpa/inet.h>
#include <sys/socket.h>

SSL* createSSLClientSocket(const char* host, int port) {
    SSL_library_init();
    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    SSL* ssl = SSL_new(ctx);
    BIO* bio = BIO_new_connect(host);
    BIO_set_conn_port(bio, std::to_string(port).c_str());
    SSL_set_bio(ssl, bio, bio);
    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return nullptr;
    }
    return ssl;
}

int main() {
    // IPv6 localhost مع المنفذ 4433
    const char* host = "[::1]";
    int port = 4433;

    SSL* ssl = createSSLClientSocket(host, port);
    if (ssl) {
        std::cout << "Test case 1: PASS" << std::endl;
        SSL_shutdown(ssl);
        SSL_free(ssl);
    } else {
        std::cout << "Test case 1: FAIL" << std::endl;
    }

    return 0;
}


/*
 *To test the code, i have to create a local IPV6 =>
openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -days 365 -nodes
openssl s_server -accept 4433 -cert cert.pem -key key.pem -www -ipv6
openssl s_server -accept [::1]:4433 -cert cert.pem -key key.pem -www
 */