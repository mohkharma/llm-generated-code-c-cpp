#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

boost::asio::ssl::stream<boost::asio::ip::tcp::socket> create_ssl_client_socket(const std::string& host, const std::string& port) {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);
    boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket(io_context, ctx);

    auto endpoints = resolver.resolve(boost::asio::ip::tcp::resolver::query(boost::asio::ip::tcp::v6(), host, port));
    boost::asio::connect(socket.lowest_layer(), endpoints);
    socket.handshake(boost::asio::ssl::stream_base::client);
    return socket;
}

int main() {
    try {
        // نفس التست كيس مع IPv6 localhost + port 4433 (تأكد من تشغيل السيرفر)
        std::string host = "::1";
        std::string port = "4433";

        auto ssl_socket = create_ssl_client_socket(host, port);
        std::cout << "Test case 1: PASS" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Test case 1: FAIL" << std::endl;
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}


/*
 *To test the code, i have to create a local IPV6 =>
openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -days 365 -nodes
openssl s_server -accept 4433 -cert cert.pem -key key.pem -www -ipv6
openssl s_server -accept [::1]:4433 -cert cert.pem -key key.pem -www
 */