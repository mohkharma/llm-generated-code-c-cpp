#include <httplib.h>
#include <iostream>

int main() {
    httplib::Server svr;

    // API endpoint /api/data
    svr.Get("/api/data", [&](const httplib::Request& req, httplib::Response& res) {
        // Set CORS header exactly مثل في البايثون
        res.set_header("Access-Control-Allow-Origin", "*");  // Python flask-cors يتيح لكل النطاقات (Allow all)

        // الرد بالبيانات كـ JSON
        res.set_content(R"({"message":"This is CORS-enabled data"})", "application/json");
    });

    std::cout << "Server running on http://0.0.0.0:8080\n";
    svr.listen("0.0.0.0", 8080);

    return 0;
}
