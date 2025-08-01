#include <iostream>
#include <string>
#include <vector>

class User {
private:
    std::string username;
    std::string password;

public:
    User(std::string username, std::string password) : username(username), password(password) {}

    bool authenticate(std::string username, std::string password) {
        if (this->username == username && this->password == password) {
            return true;
        } else {
            return false;
        }
    }
};
