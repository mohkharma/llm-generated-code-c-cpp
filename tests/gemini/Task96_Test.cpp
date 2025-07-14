#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        cerr << "Could not create server socket" << endl;
        cout << "Test case result: FAIL" << endl;
        return 1;
    }

    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(5000);

    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        cerr << "Could not bind socket to server address" << endl;
        cout << "Test case result: FAIL" << endl;
        return 1;
    }

    if (listen(serverSocket, 5) == -1) {
        cerr << "Could not listen for incoming connections" << endl;
        cout << "Test case result: FAIL" << endl;
        return 1;
    }

    cout << "Server listening on port 5000" << endl;
    cout << "Test case result: PASS" << endl;

    while (true) {
        int clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == -1) {
            cerr << "Could not accept incoming connection" << endl;
            cout << "Test case result: FAIL" << endl;
            return 1;
        }

        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived == -1) {
            cerr << "Could not read message from client" << endl;
            cout << "Test case result: FAIL" << endl;
            close(clientSocket);
            continue;
        }

        if (send(clientSocket, buffer, bytesReceived, 0) == -1) {
            cerr << "Could not echo message back to client" << endl;
            cout << "Test case result: FAIL" << endl;
            close(clientSocket);
            continue;
        }

        close(clientSocket);
    }

    close(serverSocket);
    return 0;
}
