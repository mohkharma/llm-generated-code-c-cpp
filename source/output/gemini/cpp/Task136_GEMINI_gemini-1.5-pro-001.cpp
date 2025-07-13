#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

bool authenticate(const string& username, const string& password, 
                 const unordered_map<string, string>& database) {
    if (database.count(username) && database.at(username) == password) {
        return true;
    }
    return false;
}
