
#include <iostream>
#include <string>
#include <limits>

bool authenticate() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    return (username == "admin" && password == "password123");
}

void access_resource(const std::string& resource) {
    if (resource == "1") {
        std::cout << "Accessing confidential files..." << std::endl;
    } else if (resource == "2") {
        std::cout << "Accessing financial records..." << std::endl;
    } else if (resource == "3") {
        std::cout << "Accessing employee database..." << std::endl;
    } else {
        std::cout << "Invalid resource selection." << std::endl;
    }
}
