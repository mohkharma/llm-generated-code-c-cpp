// // C++ does not have a built-in HTTP server. You need to use a library like Poco or cpp-netlib.
// // Here is a simple example using Poco:
// #include "Poco/Net/HTTPServer.h"
// #include "Poco/Net/HTTPRequestHandler.h"
// #include "Poco/Net/HTTPRequestHandlerFactory.h"
// #include "Poco/Net/HTTPServerRequest.h"
// #include "Poco/Net/HTTPServerResponse.h"
// #include "Poco/Net/ServerSocket.h"
// #include "Poco/Util/ServerApplication.h"
// #include "Poco/File.h"
//
// using namespace Poco;
// using namespace Poco::Net;
//
// class FileUploadHandler : public RequestHandler {
// public:
//     void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
//         if (request.getMethod() == "POST") {
//             std::istream& stream = request.stream();
//             File file("uploaded_file");
//             file.setBinary();
//             file.write(stream, stream.tellg());
//             response.setStatus(HTTPResponse::HTTP_OK);
//             response.setContentLength(0);
//         } else {
//             response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
//             response.setContentLength(0);
//         }
//     }
// };
//
// class FileUploadServer : public ServerApplication {
// protected:
//     void initialize(Application& self) {
//         loadConfiguration();
//         ServerApplication::initialize(self);
//     }
//
//     void uninitialize() {
//         ServerApplication::uninitialize();
//     }
//
//     void reinitialize(Application& self) {
//         ServerApplication::reinitialize(self);
//     }
//
//     void defineOptions(OptionSet& options) {
//         ServerApplication::defineOptions(options);
//     }
//
//     void handleOption(const string& name, const string& value) {
//         ServerApplication::handleOption(name, value);
//     }
//
//     int main(const vector<string>& args) {
//         HTTPServer s(new FileUploadHandlerFactory, ServerSocket(8000), new HTTPServerParams);
//         s.start();
//         waitForTerminationRequest();
//         s.stop();
//         return Application::EXIT_OK;
//     }
// };
//
// int main(int argc, char** argv) {
//     FileUploadServer app;
//     return app.run(argc, argv);
// }

#include <fstream>

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/File.h"
#include "Poco/StreamCopier.h" // Include for StreamCopier

using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Util;

class FileUploadHandler : public HTTPRequestHandler {
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override {
        if (request.getMethod() == "POST") {
            std::istream& stream = request.stream();
            std::ofstream file("uploaded_file", std::ios::binary);
            if (file.is_open()) {
                StreamCopier::copyStream(stream, file); // Use StreamCopier to copy data from the request stream to the file
                response.setStatus(HTTPResponse::HTTP_OK);
            } else {
                response.setStatus(HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            }
            response.setContentLength(0);
        } else {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentLength(0);
        }
        response.send();
    }
};

class FileUploadHandlerFactory : public HTTPRequestHandlerFactory {
public:
    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request) override {
        return new FileUploadHandler();
    }
};

class FileUploadServer : public ServerApplication {
protected:
    void initialize(Application& self) override {
        loadConfiguration(); // Load default configuration files, if any
        ServerApplication::initialize(self);
    }

    void uninitialize() override {
        ServerApplication::uninitialize();
    }

    void reinitialize(Application& self) override {
        ServerApplication::reinitialize(self);
    }

    void defineOptions(OptionSet& options) override {
        ServerApplication::defineOptions(options);
    }

    int main(const std::vector<std::string>& args) override {
        HTTPServer server(new FileUploadHandlerFactory, ServerSocket(8000), new HTTPServerParams);
        server.start();
        waitForTerminationRequest(); // Wait for CTRL-C or kill
        server.stop();
        return Application::EXIT_OK;
    }
};

int main(int argc, char** argv) {
    FileUploadServer app;
    return app.run(argc, argv);
}