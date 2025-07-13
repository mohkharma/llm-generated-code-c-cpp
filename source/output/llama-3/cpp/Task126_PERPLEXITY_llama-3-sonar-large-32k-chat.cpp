// C++ does not have a built-in way to open a web browser, so we'll use the system() function
#include <iostream>
#include <string>

void openWebpage(const std::string& url) {
    std::string command = "start " + url; // for Windows
    // std::string command = "open " + url; // for macOS
    // std::string command = "xdg-open " + url; // for Linux
    system(command.c_str());
}
