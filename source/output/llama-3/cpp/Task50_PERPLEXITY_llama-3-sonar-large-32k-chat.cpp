#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/File.h>
#include <Poco/StreamCopier.h>
#include <iostream>
#include <fstream>
#include <thread>

using namespace Poco;
using namespace Poco::Net;

class SimpleUploadHandler : public HTTPRequestHandler {
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override {
        if (request.getMethod() == "POST") {
            std::istream& stream = request.stream();
            std::ofstream file("uploaded_file", std::ios::binary);
            if (file.is_open()) {
                StreamCopier::copyStream(stream, file);
                response.setStatus(HTTPResponse::HTTP_OK);
            } else {
                response.setStatus(HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            }
        } else {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        }
        response.setContentLength(0);
        response.send();
    }
};

class SimpleUploadFactory : public HTTPRequestHandlerFactory {
public:
    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest&) override {
        return new SimpleUploadHandler();
    }
};

// ✅ دالة جديدة لتشغيل السيرفر بشكل مستقل (بدون ServerApplication)
void startPocoFileUploadServer() {
    try {
        HTTPServer server(
            new SimpleUploadFactory(),
            ServerSocket(8000),
            new HTTPServerParams);

        server.start();
        std::cout << "Poco File Upload Server listening on port 8000\n";

        // ننتظر مدة كافية لقبول اتصال واحد فقط ثم نغلق
        std::this_thread::sleep_for(std::chrono::seconds(5));

        server.stop();
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
}
