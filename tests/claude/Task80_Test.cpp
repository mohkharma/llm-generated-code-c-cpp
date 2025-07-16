#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;

// نفس الدالة بدون تعديل
ssl::stream<tcp::socket> create_ssl_ipv6_socket(const std::string& host, const std::string& port) {
    boost::asio::io_context io_context;
    ssl::context ctx(ssl::context::sslv23);
    ctx.set_default_verify_paths();

    tcp::resolver resolver(io_context);
    tcp::resolver::query query(tcp::v6(), host, port);
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    ssl::stream<tcp::socket> socket(io_context, ctx);
    boost::asio::connect(socket.lowest_layer(), endpoint_iterator);
    socket.handshake(ssl::stream_base::client);

    return socket;
}

int main() {
    try {
        // استخدم IPv6 صالح (مثلاً Google's IPv6)
        std::string host = "::1";  // localhost IPv6
        std::string port = "4433";


        auto socket = create_ssl_ipv6_socket(host, port);
        std::cout << "Test case 1: PASS" << std::endl;

        // إذا أردنا تنفيذ أكثر من حالة، نضيفها هنا بنفس الطريقة
        // لكن بما أن البايثون فيها حالة وحدة فقط، سنكتفي بهذه الحالة

    } catch (std::exception& e) {
        std::cerr << "Test case 1: FAIL" << std::endl;
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