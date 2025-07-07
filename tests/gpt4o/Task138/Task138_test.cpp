#include <iostream>
#include <set>
#include <string>
#include <cassert>

class User {
    std::string username;
    std::set<std::string> permissions;

public:
    User(const std::string& uname) : username(uname) {}

    void addPermission(const std::string& permission) {
        permissions.insert(permission);
    }

    bool hasPermission(const std::string& permission) {
        return permissions.find(permission) != permissions.end();
    }
};

void runTests() {
    User admin("admin");

    admin.addPermission("read");
    admin.addPermission("write");

    // Test cases
    assert(admin.hasPermission("read") == true);    // موجودة
    assert(admin.hasPermission("write") == true);   // موجودة
    assert(admin.hasPermission("delete") == false); // غير موجودة

    std::cout << "✅ All test cases passed successfully!" << std::endl;
}

int main() {
    try {
        runTests();
    } catch (...) {
        std::cerr << "❌ Test failed!" << std::endl;
        return 1;
    }
    return 0;
}
