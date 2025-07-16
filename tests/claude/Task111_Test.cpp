// XMLRPC_Server_Test.cpp

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <cassert>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>
#include <xmlrpc-c/client_simple.hpp>

// ---- XML-RPC Server Methods ----

class AddMethod : public xmlrpc_c::method {
public:
    AddMethod() {
        this->_signature = "i:ii"; // int return, int, int params
        this->_help = "Adds two integers";
    }
    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP) {
        int const x(paramList.getInt(0));
        int const y(paramList.getInt(1));
        *retvalP = xmlrpc_c::value_int(x + y);
    }
};

class SubtractMethod : public xmlrpc_c::method {
public:
    SubtractMethod() {
        this->_signature = "i:ii"; // int return, int, int params
        this->_help = "Subtracts second integer from first";
    }
    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP) {
        int const x(paramList.getInt(0));
        int const y(paramList.getInt(1));
        *retvalP = xmlrpc_c::value_int(x - y);
    }
};

// ---- Start Server in a Thread ----
void run_server() {
    xmlrpc_c::registry myRegistry;
    xmlrpc_c::methodPtr const addMethodP(new AddMethod);
    xmlrpc_c::methodPtr const subtractMethodP(new SubtractMethod);

    myRegistry.addMethod("add", addMethodP);
    myRegistry.addMethod("subtract", subtractMethodP);

    xmlrpc_c::serverAbyss myAbyssServer(
        xmlrpc_c::serverAbyss::constrOpt()
        .registryP(&myRegistry)
        .portNumber(8000)
        .logFileName("/dev/null")
    );

    std::cout << "XML-RPC server is running on port 8000..." << std::endl;
    myAbyssServer.run();
}

// ---- Client Test Functions ----
bool send_request_and_check(const std::string& method_name, int a, int b, int expected) {
    try {
        xmlrpc_c::clientSimple client;
        xmlrpc_c::value result;
        client.call("http://127.0.0.1:8000/RPC2", method_name, "ii", &result, a, b);
        int response = xmlrpc_c::value_int(result);
        if (response == expected) {
            std::cout << "Test " << method_name << "(" << a << ", " << b << "): PASS\n";
            return true;
        } else {
            std::cout << "Test " << method_name << "(" << a << ", " << b << "): FAIL - Expected " << expected << " got " << response << "\n";
            return false;
        }
    } catch (const std::exception& e) {
        std::cout << "Test " << method_name << "(" << a << ", " << b << "): FAIL - Exception: " << e.what() << "\n";
        return false;
    }
}

int main() {
    // Run the server in a separate thread
    std::thread server_thread(run_server);

    // Wait a moment for server to start
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Run all test cases as per python code:
    bool all_passed = true;
    all_passed &= send_request_and_check("add", 5, 3, 8);
    all_passed &= send_request_and_check("add", -5, -3, -8);
    all_passed &= send_request_and_check("add", 5, -3, 2);
    all_passed &= send_request_and_check("add", 0, 0, 0);
    all_passed &= send_request_and_check("add", 1000000, 2000000, 3000000);

    all_passed &= send_request_and_check("subtract", 10, 4, 6);
    all_passed &= send_request_and_check("subtract", -10, -4, -6);
    all_passed &= send_request_and_check("subtract", 10, -4, 14);
    all_passed &= send_request_and_check("subtract", 0, 0, 0);
    all_passed &= send_request_and_check("subtract", 3000000, 1000000, 2000000);

    if (all_passed) {
        std::cout << "All test cases passed.\n";
    } else {
        std::cout << "Some test cases failed.\n";
    }

    // Terminate server thread (ugly way)
    // NOTE: serverAbyss::run() blocks indefinitely, no direct way to stop
    // So we forcibly exit process after tests.
    std::cout << "Exiting...\n";
    exit(all_passed ? 0 : 1);
}
