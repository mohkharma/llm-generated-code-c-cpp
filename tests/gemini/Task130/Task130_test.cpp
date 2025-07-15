#include <iostream>
#include <pistache/endpoint.h>
#include <pistache/router.h>

using namespace Pistache;

class MyHandler : public Http::Handler {
public:
    HTTP_PROTOTYPE(MyHandler)

    void onRequest(const Http::Request& request, Http::ResponseWriter response) override {
        if (request.resource() == "/api/data") {
            // إضافة رأس CORS
            response.headers().add<Http::Header::AccessControlAllowOrigin>("*");
            // الرد بالبيانات JSON
            response.send(Http::Code::Ok, "{\"message\": \"This is CORS-enabled data\"}", MIME(Application, Json));
        } else {
            response.send(Http::Code::Not_Found);
        }
    }
};

int main() {
    Address addr(Ipv4::any(), Port(8080));
    auto opts = Http::Endpoint::options().threads(1);
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<MyHandler>());
    std::cout << "Server running on http://0.0.0.0:8080/api/data\n";
    server.serve();

    return 0;
}
