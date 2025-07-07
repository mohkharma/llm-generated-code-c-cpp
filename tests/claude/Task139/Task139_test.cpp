#include <iostream>
#include <cmath>
#include <cassert>

// Function to be tested
double calculateCircleArea(double radius) {
    return M_PI * radius * radius;
}

// Helper function to compare floating-point numbers
bool areEqual(double a, double b, double tolerance = 1e-9) {
    return std::fabs(a - b) <= tolerance;
}

void runTests() {
    // Test cases adapted from Python tests

    assert(areEqual(calculateCircleArea(0), 0.0));
    assert(areEqual(calculateCircleArea(1), M_PI * 1 * 1));
    assert(areEqual(calculateCircleArea(2.5), M_PI * 2.5 * 2.5));
    assert(areEqual(calculateCircleArea(10), M_PI * 10 * 10));
    assert(areEqual(calculateCircleArea(-5), M_PI * -5 * -5));
    assert(areEqual(calculateCircleArea(1000), M_PI * 1000 * 1000));
    assert(areEqual(calculateCircleArea(3.1416), M_PI * 3.1416 * 3.1416));
    assert(areEqual(calculateCircleArea(0.1), M_PI * 0.1 * 0.1));
    assert(areEqual(calculateCircleArea(1234.567), M_PI * 1234.567 * 1234.567));
    assert(areEqual(calculateCircleArea(9.99), M_PI * 9.99 * 9.99));

    std::cout << "✅ All test cases passed successfully!" << std::endl;
}

int main() {
    try {
        runTests();
    } catch (...) {
        std::cerr << "❌ A test case failed." << std::endl;
        return 1;
    }
    return 0;
}
