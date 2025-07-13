#include <iostream>
#include <string>
#include <map>
#include <uuid/uuid.h>

class SessionManager {
private:
    std::map<std::string, std::string> sessions;

public:
    SessionManager() {}

    std::string createSession(const std::string& userId) {
        std::string sessionId = generateSessionId();
        sessions[sessionId] = userId;
        return sessionId;
    }

    std::string generateSessionId() {
        uuid_t uuid;
        uuid_generate(uuid);
        char uuid_str[37];
        uuid_unparse(uuid, uuid_str);
        return std::string(uuid_str);
    }

    std::string getUserId(const std::string& sessionId) {
        return sessions[sessionId];
    }

    void invalidateSession(const std::string& sessionId) {
        sessions.erase(sessionId);
    }
};
