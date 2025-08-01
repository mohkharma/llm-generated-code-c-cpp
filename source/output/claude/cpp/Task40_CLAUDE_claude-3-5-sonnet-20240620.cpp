#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <unordered_map>

// Function to generate a random CSRF token
std::string generate_csrf_token() {
    const std::string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string token;
    srand(time(0));
    for (int i = 0; i < 32; ++i) {
        token += charset[rand() % charset.length()];
    }
    return token;
}

// Function to parse query string
std::unordered_map<std::string, std::string> parse_query_string(const std::string& query) {
    std::unordered_map<std::string, std::string> result;
    std::istringstream iss(query);
    std::string pair;
    
    while (std::getline(iss, pair, '&')) {
        size_t pos = pair.find('=');
        if (pos != std::string::npos) {
            std::string key = pair.substr(0, pos);
            std::string value = pair.substr(pos + 1);
            result[key] = value;
        }
    }
    
    return result;
}

// Function to read the stored CSRF token
std::string read_csrf_token() {
    std::ifstream file("/tmp/csrf_token.txt");
    std::string token;
    if (file.is_open()) {
        std::getline(file, token);
        file.close();
    }
    return token;
}

// Function to save the CSRF token
void save_csrf_token(const std::string& token) {
    std::ofstream file("/tmp/csrf_token.txt");
    if (file.is_open()) {
        file << token;
        file.close();
    }
}