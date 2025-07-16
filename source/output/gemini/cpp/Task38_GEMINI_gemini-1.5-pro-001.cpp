#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

void handleCGIForm() {
    char* query_string = getenv("QUERY_STRING");

    std::cout << "Content-type: text/html\n\n";

    if (query_string == nullptr) {
        std::cout << "<html><body><h1>Hello, world!</h1>"
                  << "<form method='get' action=''>"
                  << "Name: <input type='text' name='name'>"
                  << "<input type='submit' value='Submit'>"
                  << "</form></body></html>";
        return;
    }

    std::string query(query_string);
    size_t pos = query.find("name=");
    if (pos != std::string::npos) {
        std::string name = query.substr(pos + 5);
        std::cout << "<html><body>Hello, " << name << "!</body></html>";
    } else {
        std::cout << "<html><body>Invalid input</body></html>";
    }
}
