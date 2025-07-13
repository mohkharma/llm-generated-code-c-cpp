#include <iostream>
#include <string>

void accessResource(std::string resource) {
    if (resource == "admin") {
        std::cout << "Access granted to admin resource" << std::endl;
    } else if (resource == "moderator") {
        std::cout << "Access granted to moderator resource" << std::endl;
    } else if (resource == "user") {
        std::cout << "Access granted to user resource" << std::endl;
    } else {
        std::cout << "Access denied" << std::endl;
    }
}

