#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

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
    // Constructor to initialize a User object
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

// Create a User object and add it to the map
void createUser(const string& username) {
    users[username] = User(username); // Use the constructor here
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

int main() {
    // ... (your main logic using the functions above)
    return 0;
}
