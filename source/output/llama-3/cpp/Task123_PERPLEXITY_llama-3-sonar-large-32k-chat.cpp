#include <iostream>
#include <map>
#include <string>

class SessionManager {
private:
    std::map<int, std::string> sessions;

public:
    void createSession(int userId, const std::string& username) {
        this->sessions[userId] = username;
        std::cout << "Session created for user " << username << " with ID " << userId << std::endl;
    }

    std::string getUsername(int userId) {
        return this->sessions[userId];
    }

    void deleteSession(int userId) {
        if (this->sessions.find(userId) != this->sessions.end()) {
            this->sessions.erase(userId);
            std::cout << "Session deleted for user ID " << userId << std::endl;
        } else {
            std::cout << "No session found for user ID " << userId << std::endl;
        }
    }
};
