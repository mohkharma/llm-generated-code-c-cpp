#include <iostream>
#include <fstream>
#include <string>

void storeUserInFile() {
    std::string name, email;

    std::cout << "Enter name: ";
    std::getline(std::cin, name);

    std::cout << "Enter email: ";
    std::getline(std::cin, email);

    std::ofstream file("users.txt", std::ios::app);
    if (!file) {
        std::cerr << "Error: Unable to open users.txt for writing." << std::endl;
        return;
    }

    file << name << "," << email << std::endl;
    file.close();

    std::cout << "User created successfully!" << std::endl;
}
