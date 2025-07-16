#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <thread>
#include <sstream>

using boost::asio::ip::tcp;

// Abstract base class for server objects
class Object {
public:
    virtual std::string getName() const = 0;
    virtual std::string getValue() const = 0;
    virtual void setValue(const std::string& value) = 0;
    virtual ~Object() = default;
};

// Implementation of a simple string object
class StringObject : public Object {
public:
    StringObject(const std::string& name, const std::string& value)
        : name_(name), value_(value) {}

    std::string getName() const override { return name_; }
    std::string getValue() const override { return value_; }
    void setValue(const std::string& value) override { value_ = value; }

private:
    std::string name_;
    std::string value_;
};

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(std::shared_ptr<tcp::socket> socket,
            std::unordered_map<std::string, std::shared_ptr<Object>>& objects)
        : socket_(std::move(socket)), objects_(objects) {}

    void start() { readCommand(); }

private:
    void readCommand() {
        auto self = shared_from_this();
        boost::asio::async_read_until(*socket_, input_buffer_, '\n',
            [this, self](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    std::istream is(&input_buffer_);
                    std::string command;
                    std::getline(is, command);
                    processCommand(command);
                }
            });
    }

    void processCommand(const std::string& command) {
        std::istringstream iss(command);
        std::string cmd, objName, arg;
        iss >> cmd >> objName;

        if (cmd == "get_value") {
            auto it = objects_.find(objName);
            if (it != objects_.end()) {
                std::string val = it->second->getValue();
                writeResponse(val + "\n");
            } else {
                writeResponse("Error: Object not found\n");
            }
        } else if (cmd == "set_value") {
            iss >> arg;
            auto it = objects_.find(objName);
            if (it != objects_.end()) {
                it->second->setValue(arg);
                writeResponse("OK\n");
            } else {
                writeResponse("Error: Object not found\n");
            }
        } else if (cmd == "increment") {
            auto it = objects_.find(objName);
            if (it != objects_.end()) {
                int current_val = 0;
                try {
                    current_val = std::stoi(it->second->getValue());
                } catch (...) {
                    // Treat as 0 if conversion fails
                }
                it->second->setValue(std::to_string(current_val + 1));
                writeResponse("OK\n");
            } else {
                writeResponse("Error: Object not found\n");
            }
        } else {
            writeResponse("Error: Unknown command\n");
        }
    }

    void writeResponse(const std::string& response) {
        auto self = shared_from_this();
        boost::asio::async_write(*socket_, boost::asio::buffer(response),
            [this, self](boost::system::error_code ec, std::size_t) {
                if (!ec) {
                    readCommand();
                }
            });
    }

    std::shared_ptr<tcp::socket> socket_;
    boost::asio::streambuf input_buffer_;
    std::unordered_map<std::string, std::shared_ptr<Object>>& objects_;
};

class Server {
public:
    Server(boost::asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        startAccept();
    }

    void addObject(std::shared_ptr<Object> object) {
        objects_[object->getName()] = object;
    }

private:
    void startAccept() {
        auto socket = std::make_shared<tcp::socket>(acceptor_.get_executor());
        acceptor_.async_accept(*socket,
            [this, socket](boost::system::error_code ec) {
                if (!ec) {
                    std::make_shared<Session>(std::move(socket), objects_)->start();
                }
                startAccept();
            });
    }

    tcp::acceptor acceptor_;
    std::unordered_map<std::string, std::shared_ptr<Object>> objects_;
};

// Simple client to test the server
class TestClient {
public:
    TestClient(boost::asio::io_context& io_context, const std::string& host, const std::string& port)
        : socket_(io_context) {
        tcp::resolver resolver(io_context);
        boost::asio::connect(socket_, resolver.resolve(host, port));
    }

    std::string sendCommand(const std::string& cmd) {
        boost::asio::write(socket_, boost::asio::buffer(cmd + "\n"));
        boost::asio::streambuf response;
        boost::asio::read_until(socket_, response, '\n');
        std::istream is(&response);
        std::string line;
        std::getline(is, line);
        return line;
    }

private:
    tcp::socket socket_;
};

int main() {
    try {
        boost::asio::io_context io_context;

        // Start server on port 9090
        Server server(io_context, 9090);
        server.addObject(std::make_shared<StringObject>("foo", "0"));

        // Run server in a separate thread
        std::thread server_thread([&io_context]() {
            io_context.run();
        });

        // Give server a moment to start
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Create client and run tests
        boost::asio::io_context client_io_context;
        TestClient client(client_io_context, "127.0.0.1", "9090");

        bool all_passed = true;

        // Test 1: Initial value is 0
        std::string val = client.sendCommand("get_value foo");
        if (val == "0") std::cout << "test_get_initial_value: PASS\n";
        else {
            std::cout << "test_get_initial_value: FAIL (got \"" << val << "\")\n";
            all_passed = false;
        }

        // Test 2: Set value to 10
        client.sendCommand("set_value foo 10");
        val = client.sendCommand("get_value foo");
        if (val == "10") std::cout << "test_set_value: PASS\n";
        else {
            std::cout << "test_set_value: FAIL (got \"" << val << "\")\n";
            all_passed = false;
        }

        // Test 3: Increment value
        client.sendCommand("set_value foo 5");
        client.sendCommand("increment foo");
        val = client.sendCommand("get_value foo");
        if (val == "6") std::cout << "test_increment: PASS\n";
        else {
            std::cout << "test_increment: FAIL (got \"" << val << "\")\n";
            all_passed = false;
        }

        // Test 4: Multiple increments
        client.sendCommand("set_value foo 0");
        for (int i = 0; i < 5; ++i) {
            client.sendCommand("increment foo");
        }
        val = client.sendCommand("get_value foo");
        if (val == "5") std::cout << "test_multiple_increments: PASS\n";
        else {
            std::cout << "test_multiple_increments: FAIL (got \"" << val << "\")\n";
            all_passed = false;
        }

        if (all_passed) std::cout << "All tests PASSED\n";
        else std::cout << "Some tests FAILED\n";

        io_context.stop();
        server_thread.join();

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
