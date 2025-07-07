// CPP
#include <iostream>
#include <string>

std::string foo(const std::string &userInput) {
    std::string concatenatedString = "";
    while (true) {
        //press enter to finish
        if (userInput.empty()) {
            break;
        }
        concatenatedString += userInput;
    }

    return concatenatedString ;
}


