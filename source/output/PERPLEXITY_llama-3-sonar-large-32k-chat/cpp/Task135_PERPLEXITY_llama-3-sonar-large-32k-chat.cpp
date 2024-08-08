#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <cgicc/CgiEnvironment.h>
#include <iostream>
#include <string>
#include <uuid/uuid.h>

int main() {
    cgicc::Cgicc cgi;
    cgicc::CgiEnvironment env = cgi.getEnvironment();

    if (env.getRequestMethod() == "GET") {
        uuid_t uuid;
        uuid_generate_random(uuid);
        char uuid_str[37];
        uuid_unparse(uuid, uuid_str);

        std::cout << cgicc::HTTPHTMLHeader()
                  << cgicc::html()
                  << cgicc::body()
                  << cgicc::form().set("action", "").set("method", "post")
                  << cgicc::input().set("type", "hidden").set("name", "_csrf_token").set("value", uuid_str)
                  << cgicc::input().set("type", "submit").set("value", "Submit")
                  << cgicc::form()
                  << cgicc::body()
                  << cgicc::html();
    } else if (env.getRequestMethod() == "POST") {
        const std::string csrf_token_name = "_csrf_token";
        // error: ‘FormIterator’ in namespace ‘cgicc’ does not name a type; did you mean ‘form_iterator’?
        // const cgicc::FormIterator& it = cgi.getElement(csrf_token_name);
        const cgicc::form_iterator& it = cgi.getElement(csrf_token_name);
// if (it != cgi.getElements().end() && it->getValue() == env.getCookieValue("_csrf_token")) {
        if (it != cgi.getElements().end() && it->getValue() == env.getCookies()) {
            std::cout << "Form submitted successfully";
        } else {
            //Error: no matching function for call to 'cgicc::HTTPHTMLHeader::HTTPHTMLHeader(int)'
            //can't be fixed, commented.
            // std::cout << cgicc::HTTPHTMLHeader(cgicc::HTTPResponseHeader::FORBIDDEN) << "CSRF token missing or invalid";
            std::cout << cgicc::HTTPHTMLHeader() << "CSRF token missing or invalid";
        }
    }
    return 0;
}