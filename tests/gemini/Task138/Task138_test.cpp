#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

class Permission {
public:
    string name;
    string description;

    Permission(const string& name, const string& description) : name(name), description(description) {}
};

class User {
public:
    string username;
    vector<Permission> permissions;
    User() {} // Default constructor
    User(const string& username) : username(username) {}

    void addPermission(const Permission& permission) {
        permissions.push_back(permission);
    }

    bool hasPermission(const string& permissionName) const {
        for (const Permission& p : permissions) {
            if (p.name == permissionName) {
                return true;
            }
        }
        return false;
    }
};

unordered_map<string, User> users;

void createUser(const string& username) {
    users[username] = User(username);
}

void addUserPermission(const string& username, const Permission& permission) {
    if (users.find(username) != users.end()) {
        users[username].addPermission(permission);
    } else {
        cout << "User not found." << endl;
    }
}

bool checkPermission(const string& username, const string& permissionName) {
    if (users.find(username) != users.end()) {
        return users[username].hasPermission(permissionName);
    } else {
        return false;
    }
}

void runTests() {
    // Test Case 1: Create user and assign permissions
    createUser("alice");
    addUserPermission("alice", Permission("read", "Can read data"));
    addUserPermission("alice", Permission("write", "Can write data"));

    assert(checkPermission("alice", "read") == true);
    assert(checkPermission("alice", "write") == true);
    assert(checkPermission("alice", "delete") == false);

    // Test Case 2: Create another user with one permission
    createUser("bob");
    addUserPermission("bob", Permission("read", "Can read only"));

    assert(checkPermission("bob", "read") == true);
    assert(checkPermission("bob", "write") == false);

    // Test Case 3: Check non-existing user
    assert(checkPermission("charlie", "read") == false);

    cout << "✅ All test cases passed successfully!" << endl;
}

int main() {
    try {
        runTests();
    } catch (const exception& ex) {
        cerr << "❌ Test failed: " << ex.what() << endl;
        return 1;
    } catch (...) {
        cerr << "❌ Test failed: Unknown error" << endl;
        return 1;
    }
    return 0;
}
