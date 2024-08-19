#include <unordered_map>
#include <string>
#include <openssl/rand.h>

class SessionManager {
public:
    std::string createSession(const std::string& userData) {
        unsigned char sessionId[16];
        RAND_bytes(sessionId, sizeof(sessionId));
        std::string sessionIdStr(reinterpret_cast<char*>(sessionId), sizeof(sessionId));
        sessions_[sessionIdStr] = userData;
        return sessionIdStr;
    }

    bool validateSession(const std::string& sessionId) {
        return sessions_.find(sessionId) != sessions_.end();
    }

    void terminateSession(const std::string& sessionId) {
        sessions_.erase(sessionId);
    }

private:
    std::unordered_map<std::string, std::string> sessions_;
};
