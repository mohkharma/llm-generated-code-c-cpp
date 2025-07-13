#include <iostream>
#include <string>

using namespace std;

void redirect(const string &input) {
    if (input == "home") {
        cout << "Redirect to Home Page" << endl;
    } else if (input == "about") {
        cout << "Redirect to About Page" << endl;
    } else if (input == "contact") {
        cout << "Redirect to Contact Page" << endl;
    } else {
        cout << "Page not found" << endl;
    }
}
