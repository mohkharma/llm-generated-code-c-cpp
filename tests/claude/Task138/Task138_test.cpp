#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

 class PermissionManager {
private:
    std::unordered_map<std::string, std::string> users;
    std::unordered_map<std::string, std::vector<std::string>> roles;

public:
    PermissionManager() {
        roles["admin"] = {"read", "write", "delete", "manage_users"};
        roles["editor"] = {"read", "write"};
        roles["viewer"] = {"read"};
    }

    void addUser(const std::string& username, const std::string& role) {
        if (roles.find(role) == roles.end()) {
            throw std::invalid_argument("Invalid role");
        }
        users[username] = role;
    }

    void removeUser(const std::string& username) {
        users.erase(username);
    }

    void changeUserRole(const std::string& username, const std::string& newRole) {
        if (users.find(username) == users.end()) {
            throw std::invalid_argument("User not found");
        }
        if (roles.find(newRole) == roles.end()) {
            throw std::invalid_argument("Invalid role");
        }
        users[username] = newRole;
    }

    bool checkPermission(const std::string& username, const std::string& permission) {
        if (users.find(username) == users.end()) {
            return false;
        }
        const std::string& userRole = users[username];
        const std::vector<std::string>& rolePermissions = roles[userRole];
        return std::find(rolePermissions.begin(), rolePermissions.end(), permission) != rolePermissions.end();
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        for (const auto& user : users) {
            file << user.first << "," << user.second << std::endl;
        }
        file.close();
    }

    void loadFromFile(const std::string& filename) {
        users.clear();
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string username, role;
            if (std::getline(iss, username, ',') && std::getline(iss, role)) {
                users[username] = role;
            }
        }
        file.close();
    }

    bool userExists(const std::string& username) {
        return users.find(username) != users.end();
    }
};

// 🔎 وحدة اختبار صارمة
void runTests() {
    PermissionManager pm;

    pm.addUser("alice", "admin");
    pm.addUser("bob", "editor");
    pm.addUser("charlie", "viewer");

    assert(pm.checkPermission("alice", "manage_users") == true);
    assert(pm.checkPermission("bob", "write") == true);
    assert(pm.checkPermission("charlie", "delete") == false);

    pm.changeUserRole("bob", "admin");
    assert(pm.checkPermission("bob", "manage_users") == true);

    pm.removeUser("charlie");
    assert(pm.checkPermission("charlie", "read") == false);

    pm.saveToFile("permissions_test.txt");

    PermissionManager pm2;
    pm2.loadFromFile("permissions_test.txt");

    assert(pm2.checkPermission("alice", "manage_users") == true);
    assert(pm2.checkPermission("bob", "write") == true);
    assert(pm2.userExists("charlie") == false);

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
