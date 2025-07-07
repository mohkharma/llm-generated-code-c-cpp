#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

double cubeDiagonal(double volume) {
    return round(sqrt(3) * pow(volume, 1. / 3) * 100.0) / 100.0;
}

bool almostEqual(double a, double b, double eps = 1e-9) {
    return fabs(a - b) < eps;
}

void run_tests() {
    struct TestCase {
        double input;
        double expected;
    } tests[] = {
        {8, 3.46},
        {343, 12.12},
        {1157.625, 18.19},
        {27, 5.20},
        {1, 1.73},
        {64, 6.93},
        {216, 10.39},
        {1000, 17.32},
        {0.125, 0.87},
        {512, 13.86}
    };

    for (const auto& test : tests) {
        double res = cubeDiagonal(test.input);
        assert(almostEqual(res, test.expected) && "Test failed!");
    }
    cout << "ALL TESTS PASSED\n";
}

int main() {
    run_tests();
    return 0;
}
