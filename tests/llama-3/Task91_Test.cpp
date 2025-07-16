#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        cerr << "Error creating socket" << endl;
        cout << "Test case result: FAIL (socket creation)" << endl;
        return 1;
    }
    cout << "Test case result: PASS (socket creation)" << endl;

    sockaddr_in serverAddr{}, clientAddr{};

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5353);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Error binding socket" << endl;
        cout << "Test case result: FAIL (socket bind)" << endl;
        return 1;
    }
    cout << "Test case result: PASS (socket bind)" << endl;

    while (true) {
        char buffer[512];
        socklen_t clientAddrLen = sizeof(clientAddr);
        int len = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (len < 0) {
            cerr << "Error receiving data" << endl;
            cout << "Test case result: FAIL (recvfrom)" << endl;
            continue;
        }
        cout << "Test case result: PASS (recvfrom)" << endl;

        int sentLen = sendto(sock, buffer, len, 0, (struct sockaddr*)&clientAddr, clientAddrLen);
        if (sentLen < 0) {
            cerr << "Error sending data" << endl;
            cout << "Test case result: FAIL (sendto)" << endl;
        } else {
            cout << "Test case result: PASS (sendto)" << endl;
        }
    }

    return 0;
}
