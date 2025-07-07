#include <iostream>
#include <cmath>
#include <cassert>

// ✅ نفس الدالة اللي بالكود
double calculateCircleArea(double radius) {
    return M_PI * pow(radius, 2);
}

// ✅ للمقارنة الدقيقة بين الأرقام العشرية
bool areEqual(double a, double b, double tolerance = 1e-9) {
    return std::fabs(a - b) <= tolerance;
}

// ✅ نفس اختبارات Python
void runTests() {
    assert(areEqual(calculateCircleArea(0), 0.0));
    assert(areEqual(calculateCircleArea(1), M_PI * pow(1, 2)));
    assert(areEqual(calculateCircleArea(2.5), M_PI * pow(2.5, 2)));
    assert(areEqual(calculateCircleArea(10), M_PI * pow(10, 2)));
    assert(areEqual(calculateCircleArea(-5), M_PI * pow(-5, 2)));
    assert(areEqual(calculateCircleArea(1000), M_PI * pow(1000, 2)));
    assert(areEqual(calculateCircleArea(3.1416), M_PI * pow(3.1416, 2)));
    assert(areEqual(calculateCircleArea(0.1), M_PI * pow(0.1, 2)));
    assert(areEqual(calculateCircleArea(1234.567), M_PI * pow(1234.567, 2)));
    assert(areEqual(calculateCircleArea(9.99), M_PI * pow(9.99, 2)));

    std::cout << "✅ All test cases passed successfully!" << std::endl;
}

int main() {
    runTests();
    return 0;
}
