// #include <iostream>
// #include <string>
// #include <map>
// #include <cgicc/Cgicc.h>
// // #include <cgicc/HTTPForm.h>
//
// int main() {
//     cgicc::Cgicc cgi;  // Create a Cgicc object
//     std::map<std::string, std::string> cookies; // To hold cookies
//     std::string username, password;
//
//     // Retrieve cookies
//     if (cgi.getEnvironment().getCookies().size() > 0) {
//         cookies = cgi.getCookies();
//         cookies = cgi.getEnvironment().getCookies();
//     }
//
//     // Check for POST request
//     if (cgi.getElements().size() > 0) {
//         username = cgi["username"];
//         password = cgi["password"];
//         if (username == "admin" && password == "password") {
//             // Set cookie
//             std::cout << "Set-Cookie: username=" << username << "\r\n";
//             std::cout << "Location: /home\r\n\r\n"; // Redirect to home
//             return 0;
//         }
//     }
//
//     // Handle paths
//     std::string path = cgi.getPathInfo();
//     if (path == "/login") {
//         std::cout << "Content-type: text/html\r\n\r\n";
//         std::cout << "<form action=\"\" method=\"post\">";
//         std::cout << "Username: <input type=\"text\" name=\"username\"><br>";
//         std::cout << "Password: <input type=\"password\" name=\"password\"><br>";
//         std::cout << "<input type=\"submit\" value=\"Login\">";
//         std::cout << "</form>";
//     } else if (path == "/home") {
//         if (cookies.find("username") != cookies.end()) {
//             std::cout << "Content-type: text/html\r\n\r\n";
//             std::cout << "Welcome, " << cookies["username"];
//         } else {
//             std::cout << "Location: /login\r\n\r\n"; // Redirect to login
//         }
//     } else if (path == "/logout") {
//         std::cout << "Set-Cookie: username=; expires=Thu, 01 Jan 1970 00:00:00 GMT\r\n"; // Clear cookie
//         std::cout << "Location: /login\r\n\r\n"; // Redirect to login
//     }
//
//     return 0;
// }

#include <iostream>
#include <string>
#include <map>
#include <cgicc/Cgicc.h>
//fatal error: cgicc/HTTPForm.h: No such file or directory
// #include <cgicc/HTTPForm.h>

int main() {
    cgicc::Cgicc cgi;  // Create a Cgicc object
    std::map<std::string, std::string> cookies; // To hold cookies
    std::string username, password;

    // Retrieve cookies from the environment
    const cgicc::CgiEnvironment& env = cgi.getEnvironment();
    std::string cookieHeader = env.getCookies();
    if (!cookieHeader.empty()) {
        // Parse cookies from the cookie header
        size_t pos = 0;
        while ((pos = cookieHeader.find(';')) != std::string::npos) {
            std::string cookie = cookieHeader.substr(0, pos);
            size_t equalPos = cookie.find('=');
            if (equalPos != std::string::npos) {
                std::string key = cookie.substr(0, equalPos);
                std::string value = cookie.substr(equalPos + 1);
                cookies[key] = value;
            }
            cookieHeader.erase(0, pos + 1);
        }
    }

    // Check for POST request
    if (cgi.getElements().size() > 0) {
        cgicc::form_iterator username_it = cgi["username"];
        cgicc::form_iterator password_it = cgi["password"];
        if (username_it != cgi.getElements().end() && password_it != cgi.getElements().end()) {
            username = username_it->getValue();
            password = password_it->getValue();
            if (username == "admin" && password == "password") {
                // Set cookie
                std::cout << "Set-Cookie: username=" << username << "\r\n";
                std::cout << "Location: /home\r\n\r\n"; // Redirect to home
                return 0;
            }
        }
    }

    // Handle paths
    std::string path = env.getPathInfo();
    if (path == "/login") {
        std::cout << "Content-type: text/html\r\n\r\n";
        std::cout << "<form action=\"\" method=\"post\">";
        std::cout << "Username: <input type=\"text\" name=\"username\"><br>";
        std::cout << "Password: <input type=\"password\" name=\"password\"><br>";
        std::cout << "<input type=\"submit\" value=\"Login\">";
        std::cout << "</form>";
    } else if (path == "/home") {
        if (cookies.find("username") != cookies.end()) {
            std::cout << "Content-type: text/html\r\n\r\n";
            std::cout << "Welcome, " << cookies["username"];
        } else {
            std::cout << "Location: /login\r\n\r\n"; // Redirect to login
        }
    } else if (path == "/logout") {
        std::cout << "Set-Cookie: username=; expires=Thu, 01 Jan 1970 00:00:00 GMT\r\n"; // Clear cookie
        std::cout << "Location: /login\r\n\r\n"; // Redirect to login
    }

    return 0;
}