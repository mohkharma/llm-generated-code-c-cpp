#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <unordered_map>
#include <memory>
#include <thread>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class SessionManager {
public:
    std::string createSession(const std::string& userData) {
        boost::uuids::uuid sessionId = boost::uuids::random_generator()();
        sessions_[boost::uuids::to_string(sessionId)] = userData;
        return boost::uuids::to_string(sessionId);
    }

    bool validateSession(const std::string& sessionId) {
        return sessions_.find(sessionId) != sessions_.end();
    }

    void terminateSession(const std::string& sessionId) {
        sessions_.erase(sessionId);
    }

private:
    std::unordered_map<std::string, std::string> sessions_;
};

std::string extractSessionIdFromCookie(const http::request<http::string_body>& req) {
    auto it = req.find(http::field::cookie);
    if (it != req.end()) {
        auto cookie = it->value();
        auto pos = cookie.find("sessionId=");
        if (pos != std::string::npos) {
            auto start = pos + std::string("sessionId=").length();
            auto end = cookie.find(';', start);
            if (end == std::string::npos) {
                end = cookie.length();
            }
            return cookie.substr(start, end - start);
        }
    }
    return "";
}

void handleRequest(tcp::socket& socket, SessionManager& sessionManager) {
    beast::flat_buffer buffer;
    http::request<http::string_body> req;
    http::response<http::string_body> res;

    http::read(socket, buffer, req);

    if (req.target() == "/login") {
        // Authenticate user and get user data
        std::string userData = "user_data";

        std::string sessionId = sessionManager.createSession(userData);
        res.set(http::field::set_cookie, "sessionId=" + sessionId + "; HttpOnly; Secure");
        res.result(http::status::ok);
        res.body() = "Logged in";
    } else if (req.target() == "/protected") {
        std::string sessionId = extractSessionIdFromCookie(req);
        if (sessionManager.validateSession(sessionId)) {
            res.result(http::status::ok);
            res.body() = "Protected resource";
        } else {
            res.result(http::status::unauthorized);
            res.body() = "Unauthorized";
        }
    } else if (req.target() == "/logout") {
        std::string sessionId = extractSessionIdFromCookie(req);
        sessionManager.terminateSession(sessionId);
        res.result(http::status::ok);
        res.body() = "Logged out";
    } else {
        res.result(http::status::not_found);
        res.body() = "Not found";
    }

    http::write(socket, res);
}

int main() {
    net::io_context ioc;
    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));
    SessionManager sessionManager;

    for (;;) {
        tcp::socket socket(ioc);
        acceptor.accept(socket);
        // std::thread(handleRequest, std::move(socket), std::ref(sessionManager)).detach();
        std::thread([&socket, &sessionManager]() {
            handleRequest(socket, std::ref(sessionManager));
        }).detach();

    }

    return 0;
}
