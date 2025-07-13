
#include <iostream>
#include <string>
#include <stdexcept>

int convertToInt(const std::string& input) {
    try {
        return std::stoi(input);
    } catch (const std::invalid_argument& e) {
        return -1;
    } catch (const std::out_of_range& e) {
        return -1;
    }
}
