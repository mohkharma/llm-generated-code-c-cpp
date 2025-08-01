
#include <iostream>
#include <stdexcept>
#include <limits>

double divide_numbers(double a, double b) {
    if (b == 0) {
        throw std::runtime_error("Cannot divide by zero.");
    }
    return a / b;
}
