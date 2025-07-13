#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cassert>

class User {
public:
    std::string username;
    std::string password;
    std::vector<std::string> privileges;

    User() : username(""), password(""), privileges({}) {}

    User(std::string username, std::string password, std::vector<std::string> privileges)
        : username(username), password(password), privileges(privileges) {}

    bool hasPrivilege(std::string privilege) {
        for (auto &p : privileges) {
            if (p == privilege) {
                return true;
            }
        }
        return false;
    }
};

class PermissionManager {
private:
    std::map<std::string, User> users;

public:
    void addUser(std::string username, std::string password, std::vector<std::string> privileges) {
        users[username] = User(username, password, privileges);
    }

    User authenticate(std::string username, std::string password) {
        if (users.find(username) != users.end() && users[username].password == password) {
            return users[username];
        } else {
            return User();  // returns empty user
        }
    }

    bool checkPrivilege(std::string username, std::string password, std::string privilege) {
        User user = authenticate(username, password);
        return !user.username.empty() && user.hasPrivilege(privilege);
    }
};

void runTests() {
    PermissionManager manager;

    manager.addUser("admin", "password", {"read", "write", "execute"});
    manager.addUser("user", "password", {"read"});

    assert(manager.checkPrivilege("admin", "password", "write") == true);
    assert(manager.checkPrivilege("admin", "password", "delete") == false);
    assert(manager.checkPrivilege("user", "password", "read") == true);
    assert(manager.checkPrivilege("user", "password", "write") == false);
    assert(manager.checkPrivilege("user", "wrong", "read") == false);
    assert(manager.checkPrivilege("nonexistent", "password", "read") == false);

    std::cout << "✅ All test cases passed successfully!" << std::endl;
}

int main() {
    runTests();
    return 0;
}
