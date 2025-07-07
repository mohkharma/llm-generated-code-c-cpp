
#include <iostream>
#include <cmath>
#include <cassert>

double compute_area(double radius) {
    return 3.14159 * radius * radius;
}

int main() {
    const double EPSILON = 1e-5;

    assert(fabs(compute_area(0) - 0.0) < EPSILON);
    assert(fabs(compute_area(1) - (3.14159 * 1 * 1)) < EPSILON);
    assert(fabs(compute_area(2.5) - (3.14159 * 2.5 * 2.5)) < EPSILON);
    assert(fabs(compute_area(10) - (3.14159 * 10 * 10)) < EPSILON);
    assert(fabs(compute_area(-5) - (3.14159 * -5 * -5)) < EPSILON);
    assert(fabs(compute_area(1000) - (3.14159 * 1000 * 1000)) < EPSILON);
    assert(fabs(compute_area(3.1416) - (3.14159 * 3.1416 * 3.1416)) < EPSILON);
    assert(fabs(compute_area(0.1) - (3.14159 * 0.1 * 0.1)) < EPSILON);
    assert(fabs(compute_area(1234.567) - (3.14159 * 1234.567 * 1234.567)) < EPSILON);
    assert(fabs(compute_area(9.99) - (3.14159 * 9.99 * 9.99)) < EPSILON);

    std::cout << "All test cases passed!\n";
    return 0;
}
