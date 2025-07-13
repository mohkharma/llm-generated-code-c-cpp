// C++
#include <map>
#include <string>

std::map<std::string, std::string> passwords;

void signup(std::string username, std::string password) {
    passwords[username] = password;
}
