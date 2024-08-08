#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/config.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <random>
#include <thread>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

std::string generate_csrf_token() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, std::numeric_limits<uint32_t>::max());
    return std::to_string(dis(gen));
}

class session {
    std::string csrf_token_;
    std::unordered_map<std::string, std::string> settings_;

public:
    session() : csrf_token_(generate_csrf_token()) {}

    const std::string& csrf_token() const {
        return csrf_token_;
    }

    const std::unordered_map<std::string, std::string>& settings() const {
        return settings_;
    }

    void update_settings(const std::unordered_map<std::string, std::string>& new_settings) {
        settings_ = new_settings;
    }
};

class session_manager {
    std::unordered_map<std::string, std::shared_ptr<session>> sessions_;

public:
    std::shared_ptr<session> get_session(const std::string& session_id) {
        auto it = sessions_.find(session_id);
        if (it == sessions_.end()) {
            auto new_session = std::make_shared<session>();
            sessions_[session_id] = new_session;
            return new_session;
        }
        return it->second;
    }
};

void handle_request(tcp::socket& socket, session_manager& session_manager) {
    beast::flat_buffer buffer;
    http::request<http::string_body> req;
    http::response<http::string_body> res;

    http::read(socket, buffer, req);

    std::string session_id;
    auto it = req.find(http::field::cookie);
    if (it != req.end()) {
        auto cookie = it->value();
        auto pos = cookie.find("session_id=");
        if (pos != std::string::npos) {
            auto start = pos + std::string("session_id=").length();
            auto end = cookie.find(';', start);
            if (end == std::string::npos) {
                end = cookie.length();
            }
            session_id = cookie.substr(start, end - start);
        }
    }

    auto session = session_manager.get_session(session_id);

    if (req.method() == http::verb::get && req.target() == "/") {
        res.set(http::field::content_type, "text/html");
        res.body() = "<form method=\"post\" action=\"/settings\">"
                     "<input type=\"hidden\" name=\"csrf_token\" value=\"" + session->csrf_token() + "\">"
                     "<input type=\"text\" name=\"setting1\">"
                     "<input type=\"text\" name=\"setting2\">"
                     "<input type=\"submit\" value=\"Save\">"
                     "</form>";
        res.result(http::status::ok);
        res.set(http::field::set_cookie, "session_id=" + session_id);
    } else if (req.method() == http::verb::post && req.target() == "/settings") {
        std::unordered_map<std::string, std::string> new_settings;
        auto body = req.body();
        auto pos = body.find("setting1=");
        if (pos != std::string::npos) {
            auto start = pos + std::string("setting1=").length();
            auto end = body.find('&', start);
            if (end == std::string::npos) {
                end = body.length();
            }
            new_settings["setting1"] = body.substr(start, end - start);
        }
        pos = body.find("setting2=");
        if (pos != std::string::npos) {
            auto start = pos + std::string("setting2=").length();
            auto end = body.find('&', start);
            if (end == std::string::npos) {
                end = body.length();
            }
            new_settings["setting2"] = body.substr(start, end - start);
        }
        pos = body.find("csrf_token=");
        if (pos != std::string::npos) {
            auto start = pos + std::string("csrf_token=").length();
            auto end = body.find('&', start);
            if (end == std::string::npos) {
                end = body.length();
            }
            auto csrf_token = body.substr(start, end - start);
            if (csrf_token == session->csrf_token()) {
                session->update_settings(new_settings);
                res.result(http::status::found);
                res.set(http::field::location, "/");
            } else {
                res.result(http::status::forbidden);
                res.body() = "CSRF token mismatch";
            }
        } else {
            res.result(http::status::bad_request);
            res.body() = "Missing CSRF token";
        }
    } else {
        res.result(http::status::not_found);
        res.body() = "Not found";
    }

    http::write(socket, res);
}

int main(int argc, char* argv[]) {
    try {
        auto const address = net::ip::make_address("0.0.0.0");
        auto const port = static_cast<unsigned short>(std::atoi("8080"));
        auto const doc_root = ".";

        net::io_context ioc{1};
        tcp::acceptor acceptor{ioc, {address, port}};
        session_manager session_manager;

        for (;;) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);
            std::thread{std::bind(&handle_request, std::move(socket), std::ref(session_manager))}.detach();
        }
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
