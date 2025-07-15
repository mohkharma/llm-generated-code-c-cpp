#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <string>

// DNS Header structure
struct DNSHeader {
    uint16_t id;
    uint16_t flags;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
};

// DNS Question structure
struct DNSQuestion {
    std::string qname;
    uint16_t qtype;
    uint16_t qclass;
};

// Parse DNS Question from buffer starting at offset
DNSQuestion parseDNSQuestion(const uint8_t* buffer, int& offset) {
    DNSQuestion question;
    std::string domain;
    int length;
    while ((length = buffer[offset++]) != 0) {
        domain.append(reinterpret_cast<const char*>(&buffer[offset]), length);
        domain += ".";
        offset += length;
    }
    if (!domain.empty())
        domain.pop_back();  // remove trailing dot
    question.qname = domain;

    question.qtype = ntohs(*reinterpret_cast<const uint16_t*>(&buffer[offset]));
    offset += 2;
    question.qclass = ntohs(*reinterpret_cast<const uint16_t*>(&buffer[offset]));
    offset += 2;
    return question;
}

// Dummy DNS resolution function: returns a fixed IP for testing
std::vector<std::string> resolveDNS(const std::string& domain, uint16_t /*qtype*/) {
    std::vector<std::string> answers;
    if (domain == "example.com")
        answers.push_back("93.184.216.34"); // example IP
    return answers;
}

// Create DNS response packet
std::vector<uint8_t> createDNSResponse(const DNSHeader& header, const DNSQuestion& question, const std::vector<std::string>& answers) {
    std::vector<uint8_t> response;
    DNSHeader responseHeader = header;
    responseHeader.flags = htons(0x8180);  // standard response, no error
    responseHeader.ancount = htons(answers.size());

    // Insert header
    response.insert(response.end(), reinterpret_cast<uint8_t*>(&responseHeader), reinterpret_cast<uint8_t*>(&responseHeader) + sizeof(DNSHeader));

    // Question section: domain labels with length prefix
    int start = 0;
    for (size_t i = 0; i <= question.qname.size(); ++i) {
        if (i == question.qname.size() || question.qname[i] == '.') {
            uint8_t label_len = i - start;
            response.push_back(label_len);
            response.insert(response.end(), question.qname.begin() + start, question.qname.begin() + i);
            start = i + 1;
        }
    }
    response.push_back(0);  // null byte to end QNAME

    uint16_t qtype_net = htons(question.qtype);
    uint16_t qclass_net = htons(question.qclass);
    response.insert(response.end(), reinterpret_cast<uint8_t*>(&qtype_net), reinterpret_cast<uint8_t*>(&qtype_net) + 2);
    response.insert(response.end(), reinterpret_cast<uint8_t*>(&qclass_net), reinterpret_cast<uint8_t*>(&qclass_net) + 2);

    // Answer section
    for (const auto& answer : answers) {
        uint16_t pointer = htons(0xc00c); // pointer to domain name in question section
        response.insert(response.end(), reinterpret_cast<uint8_t*>(&pointer), reinterpret_cast<uint8_t*>(&pointer) + 2);
        response.insert(response.end(), reinterpret_cast<uint8_t*>(&qtype_net), reinterpret_cast<uint8_t*>(&qtype_net) + 2);
        response.insert(response.end(), reinterpret_cast<uint8_t*>(&qclass_net), reinterpret_cast<uint8_t*>(&qclass_net) + 2);
        uint32_t ttl = htonl(300);  // TTL
        response.insert(response.end(), reinterpret_cast<uint8_t*>(&ttl), reinterpret_cast<uint8_t*>(&ttl) + 4);
        uint16_t rdlength = htons(answer.length());
        response.insert(response.end(), reinterpret_cast<uint8_t*>(&rdlength), reinterpret_cast<uint8_t*>(&rdlength) + 2);
        response.insert(response.end(), answer.begin(), answer.end());
    }

    return response;
}

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        std::cout << "Test case result: FAIL (socket creation)" << std::endl;
        return 1;
    }
    std::cout << "Test case result: PASS (socket creation)" << std::endl;

    struct sockaddr_in server_addr, client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(53);

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        std::cout << "Test case result: FAIL (bind socket)" << std::endl;
        close(sockfd);
        return 1;
    }
    std::cout << "Test case result: PASS (bind socket)" << std::endl;

    std::cout << "DNS server listening on 127.0.0.1:53" << std::endl;

    while (true) {
        uint8_t buffer[512];
        socklen_t client_len = sizeof(client_addr);
        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &client_len);

        if (n < 0) {
            std::cerr << "Error receiving data" << std::endl;
            std::cout << "Test case result: FAIL (receive data)" << std::endl;
            continue;
        }
        std::cout << "Test case result: PASS (receive data)" << std::endl;

        DNSHeader* header = reinterpret_cast<DNSHeader*>(buffer);
        int offset = sizeof(DNSHeader);
        DNSQuestion question = parseDNSQuestion(buffer, offset);

        std::cout << "Received DNS query for " << question.qname << std::endl;

        std::vector<std::string> answers = resolveDNS(question.qname, question.qtype);
        std::vector<uint8_t> response = createDNSResponse(*header, question, answers);

        int sent = sendto(sockfd, response.data(), response.size(), 0, (struct sockaddr*)&client_addr, client_len);
        if (sent < 0) {
            std::cerr << "Error sending response" << std::endl;
            std::cout << "Test case result: FAIL (send response)" << std::endl;
        } else {
            std::cout << "Sent DNS response to " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;
            std::cout << "Test case result: PASS (send response)" << std::endl;
        }
    }

    close(sockfd);
    return 0;
}
