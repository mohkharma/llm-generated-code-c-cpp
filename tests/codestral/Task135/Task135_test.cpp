#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

std::string expected_token = "expected_token";

void do_session(tcp::socket socket) {
    beast::flat_buffer buffer;
    http::request<http::string_body> req;
    http::read(socket, buffer, req);

    http::response<http::string_body> res;

    if (req.method() == http::verb::get) {
        std::string body = "<form method='post'>"
                           "<input type='hidden' name='_csrf_token' value='" + expected_token + "'>"
                           "<input type='submit' value='Submit'>"
                           "</form>";
        res = {http::status::ok, req.version()};
        res.set(http::field::content_type, "text/html");
        res.body() = body;
        res.prepare_payload();
    }
    else if (req.method() == http::verb::post) {
        auto cookie = req[http::field::cookie];
        if (cookie == ("csrf_token=" + expected_token)) {
            res = {http::status::ok, req.version()};
            res.body() = "Form submitted successfully!";
        } else {
            res = {http::status::forbidden, req.version()};
            res.body() = "CSRF token validation failed";
        }
        res.prepare_payload();
    } else {
        res = {http::status::bad_request, req.version()};
        res.body() = "Invalid request method";
        res.prepare_payload();
    }

    http::write(socket, res);
    socket.shutdown(tcp::socket::shutdown_send);
}

void run_server(unsigned short port) {
    asio::io_context ioc{1};
    tcp::acceptor acceptor{ioc, {tcp::v4(), port}};
    std::cout << "Server running on port " << port << std::endl;
    for (;;) {
        tcp::socket socket{ioc};
        acceptor.accept(socket);
        std::thread([sock = std::move(socket)]() mutable {
            do_session(std::move(sock));
        }).detach();
    }
}

int main() {
    unsigned short port = 8080;

    std::thread server_thread([port] {
        run_server(port);
    });

    // Give server time to start
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Client code (simplified, just example using Boost.Beast HTTP client)
    {
        asio::io_context ioc;
        tcp::resolver resolver{ioc};
        beast::tcp_stream stream{ioc};

        auto const results = resolver.resolve("127.0.0.1", std::to_string(port));
        stream.connect(results);

        http::request<http::string_body> get_req{http::verb::get, "/", 11};
        get_req.set(http::field::host, "localhost");
        get_req.set(http::field::user_agent, "TestClient");

        http::write(stream, get_req);

        beast::flat_buffer buffer;
        http::response<http::string_body> get_res;
        http::read(stream, buffer, get_res);

        std::cout << "GET response status: " << get_res.result_int() << "\n";
        std::cout << "GET response body:\n" << get_res.body() << "\n";

        // POST with valid token
        http::request<http::string_body> post_req{http::verb::post, "/", 11};
        post_req.set(http::field::host, "localhost");
        post_req.set(http::field::user_agent, "TestClient");
        post_req.set(http::field::cookie, "csrf_token=expected_token");
        post_req.body() = "";
        post_req.prepare_payload();

        http::write(stream, post_req);

        buffer.consume(buffer.size());
        http::response<http::string_body> post_res;
        http::read(stream, buffer, post_res);

        std::cout << "POST valid response status: " << post_res.result_int() << "\n";
        std::cout << "POST valid response body:\n" << post_res.body() << "\n";

        // POST with invalid token
        http::request<http::string_body> post_bad_req{http::verb::post, "/", 11};
        post_bad_req.set(http::field::host, "localhost");
        post_bad_req.set(http::field::user_agent, "TestClient");
        post_bad_req.set(http::field::cookie, "csrf_token=bad_token");
        post_bad_req.body() = "";
        post_bad_req.prepare_payload();

        http::write(stream, post_bad_req);

        buffer.consume(buffer.size());
        http::response<http::string_body> post_bad_res;
        http::read(stream, buffer, post_bad_res);

        std::cout << "POST invalid response status: " << post_bad_res.result_int() << "\n";
        std::cout << "POST invalid response body:\n" << post_bad_res.body() << "\n";

        stream.socket().shutdown(tcp::socket::shutdown_both);
    }

    server_thread.detach();

    return 0;
}
