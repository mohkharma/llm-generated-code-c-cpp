#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Thread.h"
//error: ‘cout’ is not a member of ‘std’
#include <iostream>

class CORSRequestHandler : public Poco::Net::HTTPRequestHandler {
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override {
        response.set("Access-Control-Allow-Origin", "*");
        response.set("Access-Control-Allow-Headers", "origin, content-type, accept, authorization");
        response.set("Access-Control-Allow-Credentials", "true");
        response.set("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD");
        response.set("Access-Control-Max-Age", "1209600");

        // Handle the request
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        response.setContentType("text/plain");

        // Correctly send the response
        const char* message = "Hello, World!";
        response.sendBuffer(message, strlen(message));
    }
};

class CORSRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override {
        return new CORSRequestHandler();
    }
};

int main() {
    Poco::Net::ServerSocket svs(8080);
    Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams();
    Poco::Net::HTTPServer srv(new CORSRequestHandlerFactory(), svs, pParams);

    // Start the server
    srv.start();

    // Wait for the server to be stopped
    std::cout << "Server started on port 8080. Press Ctrl+C to stop." << std::endl;

    // Keep the server running
    Poco::Thread::sleep(Poco::Timespan::SECONDS * 3600); // Run for 1 hour, adjust as needed

    // Stop the server
    srv.stop();
    std::cout << "Server stopped." << std::endl;

    return 0;
}