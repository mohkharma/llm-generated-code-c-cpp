#include <iostream>
#include <fstream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class FileUploadServer {
public:
    FileUploadServer(boost::asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        start_accept();
    }

private:
    void start_accept() {
        auto socket = std::make_shared<tcp::socket>(acceptor_.get_executor());
        acceptor_.async_accept(*socket, [this, socket](boost::system::error_code ec) {
            if (!ec) {
                handle_connection(socket);
            }
            start_accept();
        });
    }

    void handle_connection(std::shared_ptr<tcp::socket> socket) {
        auto buffer = std::make_shared<std::vector<char>>(1024);
        boost::asio::async_read(*socket, boost::asio::buffer(*buffer),
            [this, socket, buffer](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    std::string filename(buffer->begin(), buffer->begin() + length);
                    save_file(socket, filename);
                }
            });
    }

    void save_file(std::shared_ptr<tcp::socket> socket, const std::string& filename) {
        auto file = std::make_shared<std::ofstream>("uploads/" + filename, std::ios::binary);
        if (!file->is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }
        read_file_content(socket, file);
    }

    //"error: cannot convert ‘std::ofstream’ {aka ‘std::basic_ofstream<char>’} to ‘const std::string&’ {aka ‘const std::__cxx11::basic_string<char>&’}.

    // void save_file(std::shared_ptr<tcp::socket> socket, const std::string& filename) {
    //     std::ofstream file("uploads/" + filename, std::ios::binary);
    //     auto buffer = std::make_shared<std::vector<char>>(1024);
    //     boost::asio::async_read(*socket, boost::asio::buffer(*buffer),
    //         [this, socket, buffer, &file](boost::system::error_code ec, std::size_t length) {
    //             if (!ec) {
    //                 file.write(buffer->data(), length);
    //                 save_file(socket, file);
    //             } else if (ec == boost::asio::error::eof) {
    //                 file.close();
    //                 send_confirmation(socket);
    //             }
    //         });
    // }

    void read_file_content(std::shared_ptr<tcp::socket> socket, std::shared_ptr<std::ofstream> file) {
        auto buffer = std::make_shared<std::vector<char>>(1024);
        boost::asio::async_read(*socket, boost::asio::buffer(*buffer),
            [this, socket, file, buffer](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    file->write(buffer->data(), length);
                    read_file_content(socket, file);
                } else if (ec == boost::asio::error::eof) {
                    file->close();
                    send_confirmation(socket);
                } else {
                    std::cerr << "Error while reading file: " << ec.message() << std::endl;
                }
            });
    }

    void send_confirmation(std::shared_ptr<tcp::socket> socket) {
        std::string message = "File uploaded successfully\n";
        boost::asio::async_write(*socket, boost::asio::buffer(message),
            [](boost::system::error_code ec, std::size_t) {});
    }

    tcp::acceptor acceptor_;
};

int main() {
    try {
        boost::asio::io_context io_context;
        FileUploadServer server(io_context, 8080);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}