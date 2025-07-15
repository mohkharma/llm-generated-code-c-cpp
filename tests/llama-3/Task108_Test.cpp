#include <boost/asio.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <sstream>
#include <string>

using namespace boost::asio;

std::string sendRequest(ip::tcp::socket& socket, const std::string& request) {
    std::stringstream ss_out;
    boost::archive::text_oarchive oa(ss_out);
    oa << request;
    std::string outbound = ss_out.str();

    // Send serialized request
    write(socket, buffer(outbound));

    // Read response into buffer
    streambuf response_buf;
    read(socket, response_buf.prepare(1024));
    response_buf.commit(1024);

    std::istream is(&response_buf);
    boost::archive::text_iarchive ia(is);

    std::string response;
    try {
        ia >> response;
    } catch (...) {
        response = "ERROR";
    }
    return response;
}

int main() {
    io_service io_service;
    ip::tcp::socket socket(io_service);
    ip::tcp::endpoint endpoint(ip::address::from_string("127.0.0.1"), 9090);
    socket.connect(endpoint);

    struct TestCase {
        std::string command;
        std::string expected_response;
        std::string name;
    };

    TestCase tests[] = {
        {"get_value", "Hello from server!", "test_get_initial_value"},
        {"set_value 10", "Hello from server!", "test_set_value"},
        {"increment", "Hello from server!", "test_increment"},
        {"increment", "Hello from server!", "test_multiple_increments (1)"},
        {"increment", "Hello from server!", "test_multiple_increments (2)"},
        {"increment", "Hello from server!", "test_multiple_increments (3)"},
        {"increment", "Hello from server!", "test_multiple_increments (4)"},
        {"increment", "Hello from server!", "test_multiple_increments (5)"}
    };

    bool all_passed = true;

    for (auto& test : tests) {
        std::string resp = sendRequest(socket, test.command);
        if (resp == test.expected_response) {
            std::cout << test.name << ": PASS\n";
        } else {
            std::cout << test.name << ": FAIL (got \"" << resp << "\")\n";
            all_passed = false;
        }
    }

    if (all_passed) std::cout << "All tests PASSED\n";
    else std::cout << "Some tests FAILED\n";

    socket.close();
    return 0;
}
