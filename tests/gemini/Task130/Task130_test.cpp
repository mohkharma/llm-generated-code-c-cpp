#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <curl/curl.h>
#include <pistache/endpoint.h>
#include <pistache/router.h>

using namespace Pistache;

// ======= السيرفر =======

class MyHandler : public Http::Handler {
public:
    HTTP_PROTOTYPE(MyHandler)

    void onRequest(const Http::Request& request, Http::ResponseWriter response) override {
        if (request.resource() == "/api/data") {
            response.headers().add<Http::Header::AccessControlAllowOrigin>("*");
            response.send(Http::Code::Ok, "{\"name\": \"John Doe\", \"age\": 30}");
        } else {
            response.send(Http::Code::Not_Found);
        }
    }
};

void run_server() {
    Address addr(Ipv4::any(), Port(9080));
    auto opts = Http::Endpoint::options().threads(1);
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<MyHandler>());
    std::cout << "Server is running on port 9080\n";
    server.serve();
}

// ======= اختبار libcurl =======

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

static size_t HeaderCallback(char* buffer, size_t size, size_t nitems, void* userdata)
{
    size_t num_bytes = size * nitems;
    std::string header_line(buffer, num_bytes);
    std::string* headers = (std::string*)userdata;
    headers->append(header_line);
    return num_bytes;
}

bool test_cors_header_improved() {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to init curl\n";
        return false;
    }
    std::string response_body;
    std::string response_headers;

    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:9080/api/data");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_headers);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
        curl_easy_cleanup(curl);
        return false;
    }

    long response_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    curl_easy_cleanup(curl);

    if (response_code != 200) {
        std::cerr << "FAIL: HTTP response code not 200\n";
        return false;
    }

    if (response_headers.find("Access-Control-Allow-Origin: *") == std::string::npos) {
        std::cerr << "FAIL: CORS header not found\n";
        return false;
    }

    if (response_body.find("\"name\"") == std::string::npos || response_body.find("\"age\"") == std::string::npos) {
        std::cerr << "FAIL: Response body does not contain expected data\n";
        return false;
    }

    std::cout << "PASS: CORS header and response verified\n";
    return true;
}

// ======= main =======

int main() {
    // شغّل السيرفر في خيط منفصل
    std::thread server_thread(run_server);

    // انتظر 1 ثانية ليبدأ السيرفر ويبدأ بالاستماع
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Running CORS test...\n";
    bool result = test_cors_header_improved();

    if (result)
        std::cout << "Test case 1: PASS\n";
    else
        std::cout << "Test case 1: FAIL\n";

    // غلق السيرفر (Pistache لا يدعم غلق بسيط، لذلك نغلق البرنامج كلياً)
    // في تطبيق حقيقي، تحتاج آلية غلق نظيفة
    server_thread.detach();  // فقط لفصل الخيط بدون انتظار، أو تقتل البرنامج

    return 0;
}
