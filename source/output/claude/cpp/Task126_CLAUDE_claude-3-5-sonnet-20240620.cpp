#include <iostream>
#include <string>
#include <cstdlib>

void redirect_user(std::istream& in, std::ostream& out) {
    out << "Select a destination:" << std::endl;
    out << "1. Google" << std::endl;
    out << "2. YouTube" << std::endl;
    out << "3. Wikipedia" << std::endl;

    out << "Enter your choice (1-3): ";
    std::string choice;
    in >> choice;

    std::string url;
    if (choice == "1") {
        url = "https://www.google.com";
    } else if (choice == "2") {
        url = "https://www.youtube.com";
    } else if (choice == "3") {
        url = "https://www.wikipedia.org";
    } else {
        out << "Invalid choice. Please try again." << std::endl;
        return;
    }

     out << url << std::endl;

#ifdef _WIN32
    std::string command = "start " + url;
#elif __APPLE__
    std::string command = "open " + url;
#else
    std::string command = "xdg-open " + url;
#endif

    system(command.c_str());
}
