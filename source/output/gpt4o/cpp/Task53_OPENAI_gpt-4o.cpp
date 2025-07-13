#include <iostream>
#include <string>

class UserSession {
private:
    std::string sessionId;
    std::string userId;

public:
    UserSession(std::string sessionId, std::string userId) {
        this->sessionId = sessionId;
        this->userId = userId;
    }

    std::string toString() {
        return "Session ID: " + sessionId + ", User ID: " + userId;
    }
};
