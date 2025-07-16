#include <iostream>
#include <string>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

void handleSettingsForm() {
    cgicc::Cgicc cgi;
    std::string csrfToken = "random_token_here";

    std::cout << "Content-type:text/html\r\n\r\n";

    if (cgi.getEnvironment().getRequestMethod() == "POST") {
        if (!cgi("csrf_token").empty() && cgi("csrf_token") == csrfToken) {
            std::cout << "<html><body><h2>Settings updated successfully</h2></body></html>";
        } else {
            std::cout << "<html><body><h2>CSRF token is invalid</h2></body></html>";
        }
    } else {
        std::cout << "<html><body>";
        std::cout << "<form action=\"\" method=\"post\">";
        std::cout << "<input type=\"hidden\" name=\"csrf_token\" value=\"" << csrfToken << "\">";
        std::cout << "<label>Username:</label>";
        std::cout << "<input type=\"text\" name=\"username\"><br><br>";
        std::cout << "<label>Email:</label>";
        std::cout << "<input type=\"email\" name=\"email\"><br><br>";
        std::cout << "<input type=\"submit\" value=\"Update Settings\">";
        std::cout << "</form>";
        std::cout << "</body></html>";
    }
}
