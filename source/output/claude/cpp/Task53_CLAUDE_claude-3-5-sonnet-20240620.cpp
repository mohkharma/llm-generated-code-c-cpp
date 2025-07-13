
#include <iostream>
#include <unordered_map>
#include <string>
#include <ctime>
#include <random>

class Session {
public:
    std::string sessionId;
    std::string userId;
    time_t createdAt;
    time_t lastAccessed;

    //error: no matching function for call to ‘Session::Session()’. Missing default constructor add the below default constructor
    Session() {
        sessionId = generateUUID();
        createdAt = time(nullptr);
        lastAccessed = createdAt;
    }
    Session(const std::string& userId) : userId(userId) {
        sessionId = generateUUID();
        createdAt = time(nullptr);
        lastAccessed = createdAt;
    }
 public:
    std::string generateUUID() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 15);
        static const char* chars = "0123456789abcdef";

        std::string uuid;
        for (int i = 0; i < 32; i++) {
            uuid += chars[dis(gen)];
            if (i == 7 || i == 11 || i == 15 || i == 19) {
                uuid += '-';
            }
        }
        return uuid;
    }
};

class SessionManager {
public:
    std::unordered_map<std::string, Session> sessions;
    time_t sessionTimeout;

public:
    SessionManager(time_t timeout = 1800) : sessionTimeout(timeout) {}

    std::string createSession(const std::string& userId) {
        Session session(userId);
        sessions[session.sessionId] = session;
        return session.sessionId;
    }

    Session* getSession(const std::string& sessionId) {
        auto it = sessions.find(sessionId);
        if (it != sessions.end()) {
            Session& session = it->second;
            time_t now = time(nullptr);
            if (now - session.lastAccessed > sessionTimeout) {
                destroySession(sessionId);
                return nullptr;
            }
            session.lastAccessed = now;
            return &session;
        }
        return nullptr;
    }

    void destroySession(const std::string& sessionId) {
        sessions.erase(sessionId);
    }

    void cleanupExpiredSessions() {
        time_t now = time(nullptr);
        for (auto it = sessions.begin(); it != sessions.end();) {
            if (now - it->second.lastAccessed > sessionTimeout) {
                it = sessions.erase(it);
            } else {
                ++it;
            }
        }
    }
};