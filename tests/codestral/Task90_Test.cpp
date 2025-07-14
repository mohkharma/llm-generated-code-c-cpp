#include <iostream>
#include <vector>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

std::vector<int> clients;

void handle_client(int client_socket) {
    char buffer[1024];
    while (true) {
        int bytes_received = recv(client_socket, buffer, 1024, 0);
        if (bytes_received <= 0) {
            // العميل قطع الاتصال
            break;
        }
        for (int client : clients) {
            if (client != client_socket) {
                send(client, buffer, bytes_received, 0);
            }
        }
    }
    // حذف العميل من القائمة (لو حبيت تضيف هذا)
    // هنا قد تحتاج إلى حماية بال mutex لو استعملت في تطبيق حقيقي
    close(client_socket);
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, SOMAXCONN);

    while (true) {
        int client_socket = accept(server_socket, nullptr, nullptr);
        clients.push_back(client_socket);
        std::thread(handle_client, client_socket).detach();
    }

    return 0;
}
