
#include <iostream>
#include <unordered_map>
#include <chrono>
#include <ctime>
#include <string>
#include <algorithm>
#include <random>
#include <thread>

class Session {
public:
    std::string sessionId;
    std::string userId;
    std::chrono::system_clock::time_point creationTime;
    std::chrono::system_clock::time_point lastActivity;

    //error: no matching function for call to ‘Session::Session()’
    //add default constructor
    Session() = default;  // Add this line

    Session(const std::string& userId) : userId(userId) {
        sessionId = generateUUID();
        creationTime = std::chrono::system_clock::now();
        lastActivity = creationTime;
    }

private:
    std::string generateUUID() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 15);
        static const char* digits = "0123456789abcdef";

        std::string uuid(36, '-');
        for (int i = 0; i < 36; i++) {
            if (i == 8 || i == 13 || i == 18 || i == 23) continue;
            uuid[i] = digits[dis(gen)];
        }
        return uuid;
    }
};

class SessionManager {
private:
    std::unordered_map<std::string, Session> sessions;
    std::chrono::seconds sessionTimeout;

public:
    SessionManager(int timeoutSeconds = 1800) : sessionTimeout(timeoutSeconds) {}

    std::string createSession(const std::string& userId) {
        Session session(userId);
        sessions[session.sessionId] = session;
        return session.sessionId;
    }

    Session* getSession(const std::string& sessionId) {
        auto it = sessions.find(sessionId);
        if (it != sessions.end()) {
            auto now = std::chrono::system_clock::now();
            if (now - it->second.lastActivity > sessionTimeout) {
                destroySession(sessionId);
                return nullptr;
            }
            it->second.lastActivity = now;
            return &(it->second);
        }
        return nullptr;
    }

    void destroySession(const std::string& sessionId) {
        sessions.erase(sessionId);
    }

    void cleanupExpiredSessions() {
        auto now = std::chrono::system_clock::now();
        for (auto it = sessions.begin(); it != sessions.end();) {
            if (now - it->second.lastActivity > sessionTimeout) {
                it = sessions.erase(it);
            } else {
                ++it;
            }
        }
    }
};
