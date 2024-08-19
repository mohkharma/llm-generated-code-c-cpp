#include <boost/asio.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <string>
#include <sstream>

using namespace boost::asio;
using namespace boost::serialization;

class MyService {
public:
    std::string getData() {
        return "Hello from server!";
    }

    void setData(const std::string& data) {
        std::cout << "Received data from client: " << data << std::endl;
    }
};

int main() {
    io_service io;
    ip::tcp::acceptor acceptor(io, ip::tcp::endpoint(ip::tcp::v4(), 18861));
    ip::tcp::socket socket(io);

    acceptor.accept(socket);

    // Create a streambuf to read from and write to the socket
    boost::asio::streambuf buf;

    // Create input and output streams from the streambuf
    std::istream is(&buf);
    std::ostream os(&buf);

    // Read from the socket into the streambuf
    boost::asio::read(socket, buf);

    // Create the input archive from the stream
    boost::archive::text_iarchive ia(is);
    boost::archive::text_oarchive oa(os);

    MyService service;
    std::string data;

    while (true) {
        // Read data from the client
        ia >> data;
        service.setData(data);

        // Prepare the response
        std::string response = service.getData();
        oa << response;

        // Write the response back to the socket
        boost::asio::write(socket, buf);
        
        // Clear the buffer for the next iteration
        buf.consume(buf.size());
    }

    return 0;
}
