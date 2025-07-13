#include <iostream>
#include <map>
#include <string>

class User {
public:
    std::string username;
    std::string password;

    //error: no matching function for call to ‘User::User()’
    // Default constructor
    User() : username(""), password("") {}

    User(std::string username, std::string password) {
        this->username = username;
        this->password = password;
    }
};

std::map<std::string, User> users;

void signup() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    users[username] = User(username, password);
    std::cout << "Signup successful!" << std::endl;
}
