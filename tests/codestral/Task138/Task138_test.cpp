#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

class User {
private:
    std::string name;
    std::vector<std::string> permissions;

public:
    User(std::string name, std::vector<std::string> permissions) {
        this->name = name;
        this->permissions = permissions;
    }

    bool hasPermission(std::string permission) {
        return std::find(permissions.begin(), permissions.end(), permission) != permissions.end();
    }
};

void runTests() {
    User user("John", {"read", "write"});

    assert(user.hasPermission("read") == true);
    assert(user.hasPermission("execute") == false);

    std::cout << "✅ All test cases passed successfully!" << std::endl;
}

int main() {
    try {
        runTests();
    } catch (const std::exception& ex) {
        std::cerr << "❌ Test failed: " << ex.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ Test failed: Unknown error" << std::endl;
        return 1;
    }
    return 0;
}
