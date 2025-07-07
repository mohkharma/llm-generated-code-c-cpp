#include <iostream>
#include <cassert>
#include <cmath>

double cubeDiagonal(double volume) {
    double sideLength = cbrt(volume);
    double diagonalLength = round(sideLength * sqrt(3) * 100.0) / 100.0;
    return diagonalLength;
}

bool almostEqual(double a, double b, double epsilon = 1e-9) {
    return std::fabs(a - b) < epsilon;
}

void run_tests() {
    struct TestCase {
        double input;
        double expected;
    };

    TestCase tests[] = {
        {8, 3.46},
        {343, 12.12},
        {1157.625, 18.19},
        {27, 5.2},
        {1, 1.73},
        {64, 6.93},
        {216, 10.39},
        {1000, 17.32},
        {0.125, 0.87},
        {512, 13.86}
    };

    for (int i = 0; i < 10; ++i) {
        double result = cubeDiagonal(tests[i].input);
        assert(almostEqual(result, tests[i].expected) && "Test failed!");
    }
    std::cout << "ALL TESTS PASSED\n";
}

int main() {
    run_tests();
    return 0;
}
