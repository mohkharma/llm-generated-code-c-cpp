#include <iostream>
#include <string>

void handle_redirect(std::istream& in, std::ostream& out) {
    std::string userInput;
    out << "Enter your input: ";
    in >> userInput;

    if (userInput == "home") {
        out << "Redirecting to home page..." << std::endl;
    } else if (userInput == "about") {
        out << "Redirecting to about page..." << std::endl;
    } else if (userInput == "contact") {
        out << "Redirecting to contact page..." << std::endl;
    } else {
        out << "Invalid input. Redirecting to default page..." << std::endl;
    }
}
