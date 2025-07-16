#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <unistd.h>

int create_ssl_client_socket_ipv6(const char *hostname, int port) {
    // Initialize OpenSSL
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    // Create a TCP socket using IPv6
    int sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    // Create an SSL context
    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        std::cerr << "Failed to create SSL context" << std::endl;
        close(sockfd);
        return -1;
    }

    // Create an SSL object
    SSL *ssl = SSL_new(ctx);
    if (!ssl) {
        std::cerr << "Failed to create SSL object" << std::endl;
        SSL_CTX_free(ctx);
        close(sockfd);
        return -1;
    }

    // Bind the SSL object to the socket
    if (SSL_set_fd(ssl, sockfd) <= 0) {
        std::cerr << "Failed to bind SSL object to socket" << std::endl;
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockfd);
        return -1;
    }

    // Connect to the server
    sockaddr_in6 server_addr{};
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(port);
    inet_pton(AF_INET6, hostname, &server_addr.sin6_addr);
    if (connect(sockfd, (sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to connect to server" << std::endl;
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockfd);
        return -1;
    }

    // Establish SSL connection
    if (SSL_connect(ssl) <= 0) {
        std::cerr << "Failed to establish SSL connection" << std::endl;
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockfd);
        return -1;
    }

    return sockfd;
}

int main() {
    const char* host = "::1"; // IPv6 localhost
    int port = 4433;          // المنفذ المستخدم في السيرفر المحلي

    int sockfd = create_ssl_client_socket_ipv6(host, port);
    if (sockfd >= 0) {
        std::cout << "Test case 1: PASS" << std::endl;
        close(sockfd);
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