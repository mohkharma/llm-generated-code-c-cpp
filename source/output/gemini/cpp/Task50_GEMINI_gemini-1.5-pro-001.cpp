#include <iostream>
#include <fstream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#define PORT 65432

using namespace std;

void handleClient(int clientSocket) {
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    // Receive filename and filesize
    recv(clientSocket, buffer, BUFFER_SIZE, 0);
    string filename(buffer);

    recv(clientSocket, buffer, BUFFER_SIZE, 0);
    long filesize = stol(string(buffer));

    cout << "Receiving file: " << filename << " (" << filesize << " bytes)" << endl;

    // Receive and save the file
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    long bytesReceived = 0;
    while (bytesReceived < filesize) {
        int bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesRead <= 0) {
            cerr << "Error receiving file data" << endl;
            break;
        }

        file.write(buffer, bytesRead);
        bytesReceived += bytesRead;
    }

    file.close();

    cout << filename << " uploaded successfully!" << endl;
    send(clientSocket, "File uploaded successfully!", 26, 0);
}

// ✅ نقطة التشغيل لاستخدامها من ملف الاختبار
void start_server() {
    int server_fd, clientSocket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        return;
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return;
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        return;
    }

    std::cout << "Gemini server listening on port " << PORT << "...\n";

    // 🔁 يقبل اتصال واحد فقط
    clientSocket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if (clientSocket < 0) {
        perror("accept failed");
        return;
    }

    handleClient(clientSocket);
    close(clientSocket);
    close(server_fd);
    close(clientSocket);
    close(server_fd);
}
