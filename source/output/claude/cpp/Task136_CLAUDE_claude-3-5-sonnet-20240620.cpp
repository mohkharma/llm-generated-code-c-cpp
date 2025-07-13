
#include <iostream>
#include <unordered_map>
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

std::unordered_map<std::string, std::string> users;

std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

bool register_user(const std::string& username, const std::string& password) {
    if (users.find(username) != users.end()) {
        return false;
    }
    users[username] = sha256(password);
    return true;
}

bool login(const std::string& username, const std::string& password) {
    auto it = users.find(username);
    if (it == users.end()) {
        return false;
    }
    return it->second == sha256(password);
}
