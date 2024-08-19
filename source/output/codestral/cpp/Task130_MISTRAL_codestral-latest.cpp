#include <httplib.h>

int main() {
    httplib::Server svr;

    svr.set_mount_point("/", "./www");
    //can't be fixed,  error: ‘class httplib::Server’ has no member named ‘set_before_response’
    // svr.set_before_response([&](const httplib::Request& req, httplib::Response& res) {
    //     res.set_header("Access-Control-Allow-Origin", "http://example.com");
    // });

    svr.listen("0.0.0.0", 8080);
}
