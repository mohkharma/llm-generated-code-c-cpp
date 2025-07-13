#include <cpprest/http_listener.h>
#include <cpprest/http_client.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
using namespace web::http::client;

int main() {
    http_listener listener(U("http://localhost:34568/test"));

    listener.support(methods::GET, [](http_request request){
        request.reply(status_codes::OK, U("GET response"));
    });

    listener.support(methods::POST, [](http_request request){
        request.extract_string().then([=](std::string body){
            if(body == "valid_token") {
                request.reply(status_codes::OK, U("Form submitted successfully!"));
            } else {
                request.reply(status_codes::Forbidden, U("CSRF token validation failed"));
            }
        }).wait();
    });

    listener.open().wait();

    http_client client(U("http://localhost:34568/test"));

    // اختبار GET
    auto responseGet = client.request(methods::GET).get();
    auto bodyGet = responseGet.extract_string().get();
    std::cout << "[GET] Status: " << responseGet.status_code() << ", Body: " << bodyGet << "\n";

    // اختبار POST صالح
    http_request reqPost(methods::POST);
    reqPost.set_body("valid_token");
    auto responsePost = client.request(reqPost).get();
    auto bodyPost = responsePost.extract_string().get();
    std::cout << "[POST valid] Status: " << responsePost.status_code() << ", Body: " << bodyPost << "\n";

    // اختبار POST غير صالح
    http_request reqPostBad(methods::POST);
    reqPostBad.set_body("bad_token");
    auto responsePostBad = client.request(reqPostBad).get();
    auto bodyPostBad = responsePostBad.extract_string().get();
    std::cout << "[POST invalid] Status: " << responsePostBad.status_code() << ", Body: " << bodyPostBad << "\n";

    listener.close().wait();

    return 0;
}
