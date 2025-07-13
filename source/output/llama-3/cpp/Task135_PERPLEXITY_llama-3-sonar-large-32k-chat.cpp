#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <cgicc/CgiEnvironment.h>
#include <iostream>
#include <string>
#include <uuid/uuid.h>

using namespace std;
using namespace cgicc;

void handleRequest() {
    Cgicc cgi;
    CgiEnvironment env = cgi.getEnvironment();
    const string csrf_token_name = "_csrf_token";

    if (env.getRequestMethod() == "GET") {
        // توليد UUID
        uuid_t uuid;
        uuid_generate_random(uuid);
        char uuid_str[37];
        uuid_unparse(uuid, uuid_str);

        // عرض النموذج مع CSRF token
        cout << HTTPHTMLHeader()
             << html()
             << body()
             << form().set("action", "").set("method", "post")
             << input().set("type", "hidden").set("name", csrf_token_name).set("value", uuid_str)
             << input().set("type", "submit").set("value", "Submit")
             << form()
             << body()
             << html();
    } else if (env.getRequestMethod() == "POST") {
        // استخراج الـ CSRF token من الطلب
        form_iterator it = cgi.getElement(csrf_token_name);

        // لا يوجد كود لتخزين أو مقارنة قيمة التوكن مع cookie، لذا نقارن بوجوده فقط هنا كمنطق مبدئي
        if (it != cgi.getElements().end() && !it->getValue().empty()) {
            cout << HTTPHTMLHeader()
                 << "Form submitted successfully.";
        } else {
            cout << HTTPHTMLHeader()
                 << "CSRF token missing or invalid.";
        }
    }
}


