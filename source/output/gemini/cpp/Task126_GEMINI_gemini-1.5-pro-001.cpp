#include <iostream>
#include <string>
#include <cctype>

void redirect_page(std::istream& in, std::ostream& out) {
    std::string choice;

    out << "Enter your destination (A, B, or C): ";
    in >> choice;

    for (char &c : choice) {
        c = std::toupper(c);
    }

    if (choice == "A") {
        out << "Redirecting to page A..." << std::endl;
    } else if (choice == "B") {
        out << "Redirecting to page B..." << std::endl;
    } else if (choice == "C") {
        out << "Redirecting to page C..." << std::endl;
    } else {
        out << "Invalid choice. Please enter A, B, or C." << std::endl;
    }
}
