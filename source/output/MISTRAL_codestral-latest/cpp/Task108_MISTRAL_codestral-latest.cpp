#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <unordered_map>

using boost::asio::ip::tcp;

class Object {
public:
    virtual std::string getName() const = 0;
    virtual std::string getValue() const = 0;
    virtual void setValue(const std::string& value) = 0;
};

class StringObject : public Object {
public:
    StringObject(const std::string& name, const std::string& value)
        : name_(name), value_(value) {}

    std::string getName() const override {
        return name_;
    }

    std::string getValue() const override {
        return value_;
    }

    void setValue(const std::string& value) override {
        value_ = value;
    }

private:
    std::string name_;
    std::string value_;
};

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(std::shared_ptr<tcp::socket> socket,
            const std::unordered_map<std::string, std::shared_ptr<Object>>& objects)
        : socket_(std::move(socket)), objects_(objects) {}

    void start() {
        readCommand();
    }

private:
    void readCommand() {
        boost::asio::async_read_until(*socket_, input_buffer_, '\n',
            [this](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    std::istream is(&input_buffer_);
                    std::string command;
                    std::getline(is, command);
                    processCommand(command);
                }
            });
    }

    void processCommand(const std::string& command) {
        // Parse the command and perform the appropriate action on the server's objects
        // ...
    }

    std::shared_ptr<tcp::socket> socket_;
    boost::asio::streambuf input_buffer_;
    const std::unordered_map<std::string, std::shared_ptr<Object>>& objects_;
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

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: server <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;
        Server server(io_context, std::atoi(argv[1]));

        // Add objects to the server
        server.addObject(std::make_shared<StringObject>("foo", "bar"));

        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}


// #include <boost/asio.hpp>
// #include <iostream>
// #include <memory>
// #include <unordered_map>
//
// using boost::asio::ip::tcp;
//
// class Object {
// public:
//     virtual std::string getName() const = 0;
//     virtual std::string getValue() const = 0;
//     virtual void setValue(const std::string& value) = 0;
// };
//
// class StringObject : public Object {
// public:
//     StringObject(const std::string& name, const std::string& value)
//         : name_(name), value_(value) {}
//
//     std::string getName() const override {
//         return name_;
//     }
//
//     std::string getValue() const override {
//         return value_;
//     }
//
//     void setValue(const std::string& value) override {
//         value_ = value;
//     }
//
// private:
//     std::string name_;
//     std::string value_;
// };
//
// class Server {
// public:
//     Server(boost::asio::io_context& io_context, short port)
//         : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
//         startAccept();
//     }
//
//     void addObject(std::shared_ptr<Object> object) {
//         objects_[object->getName()] = object;
//     }
//
// private:
//     void startAccept() {
//         auto socket = std::make_shared<tcp::socket>(acceptor_.get_executor());
//         acceptor_.async_accept(*socket,
//             [this, socket](boost::system::error_code ec) {
//                 if (!ec) {
//                     std::make_shared<Session>(std::move(socket), objects_)->start();
//                 }
//                 startAccept();
//             });
//     }
//
//     tcp::acceptor acceptor_;
//     std::unordered_map<std::string, std::shared_ptr<Object>> objects_;
// };
//
// class Session : public std::enable_shared_from_this<Session> {
// public:
//     Session(std::shared_ptr<tcp::socket> socket,
//             const std::unordered_map<std::string, std::shared_ptr<Object>>& objects)
//         : socket_(std::move(socket)), objects_(objects) {}
//
//     void start() {
//         readCommand();
//     }
//
// private:
//     void readCommand() {
//         boost::asio::async_read_until(*socket_, input_buffer_, '\n',
//             [this](boost::system::error_code ec, std::size_t length) {
//                 if (!ec) {
//                     std::istream is(&input_buffer_);
//                     std::string command;
//                     std::getline(is, command);
//                     processCommand(command);
//                 }
//             });
//     }
//
//     void processCommand(const std::string& command) {
//         // Parse the command and perform the appropriate action on the server's objects
//         // ...
//     }
//
//     std::shared_ptr<tcp::socket> socket_;
//     boost::asio::streambuf input_buffer_;
//     const std::unordered_map<std::string, std::shared_ptr<Object>>& objects_;
// };
//
// int main(int argc, char* argv[]) {
//     try {
//         if (argc != 2) {
//             std::cerr << "Usage: server <port>\n";
//             return 1;
//         }
//
//         boost::asio::io_context io_context;
//         Server server(io_context, std::atoi(argv[1]));
//
//         // Add objects to the server
//         server.addObject(std::make_shared<StringObject>("foo", "bar"));
//
//         io_context.run();
//     } catch (std::exception& e) {
//         std::cerr << "Exception: " << e.what() << "\n";
//     }
//
//     return 0;
// }
