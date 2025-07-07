
#include <iostream>
#include <cmath>
#include <cassert>

double compute_area(double radius) {
    return M_PI * radius * radius;
}

int main() {
    const double EPSILON = 1e-5;

    assert(fabs(compute_area(0) - 0.0) < EPSILON);
    assert(fabs(compute_area(1) - (M_PI * 1 * 1)) < EPSILON);
    assert(fabs(compute_area(2.5) - (M_PI * 2.5 * 2.5)) < EPSILON);
    assert(fabs(compute_area(10) - (M_PI * 10 * 10)) < EPSILON);
    assert(fabs(compute_area(-5) - (M_PI * -5 * -5)) < EPSILON);
    assert(fabs(compute_area(1000) - (M_PI * 1000 * 1000)) < EPSILON);
    assert(fabs(compute_area(3.1416) - (M_PI * 3.1416 * 3.1416)) < EPSILON);
    assert(fabs(compute_area(0.1) - (M_PI * 0.1 * 0.1)) < EPSILON);
    assert(fabs(compute_area(1234.567) - (M_PI * 1234.567 * 1234.567)) < EPSILON);
    assert(fabs(compute_area(9.99) - (M_PI * 9.99 * 9.99)) < EPSILON);

    std::cout << "All test cases passed!\n";
    return 0;
}
