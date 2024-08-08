#include <iostream>
#include <string>
#include <cstring>

int main() {
    char *query_string = getenv("QUERY_STRING");
    if (query_string == nullptr) {
        std::cout << "Content-type: text/html\n\n";
        std::cout << "<html><body><h1>Hello, world!</h1><form method='get' action=''>Name: <input type='text' name='name'><input type='submit' value='Submit'></form></body></html>";
        return 0;
    }

    // Parse query string
    std::string query(query_string);
    size_t pos = query.find("name=");
    if (pos != std::string::npos) {
        std::string name = query.substr(pos + 5);
        std::cout << "Content-type: text/html\n\n";
        std::cout << "<html><body>Hello, " << name << "!</body></html>";
    } else {
        std::cout << "Content-type: text/html\n\n";
        std::cout << "<html><body>Invalid input</body></html>";
    }

    return 0;
}
