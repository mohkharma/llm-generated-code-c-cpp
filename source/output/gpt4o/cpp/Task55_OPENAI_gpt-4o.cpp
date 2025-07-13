#include <iostream>
#include <regex>
using namespace std;

bool validateEmail(const string &email) {
    const regex pattern("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$");
    return regex_match(email, pattern);
}

