// Task167_Test.cpp
#include <iostream>
#include <sstream>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <string>

// الحل كما أعطيت
class Solution {
public:
    static double cubeDiagonal(double volume) {
        double side = std::cbrt(volume);
        double diagonal = std::sqrt(3.0) * side;
        return std::round(diagonal * 100.0) / 100.0;
    }
};

// دالة مساعدة للمقارنة مع تقريب 2 أرقام عشرية (لضمان نفس السلوك)
bool almostEqual(double a, double b, double epsilon = 1e-9) {
    return std::fabs(a - b) < epsilon;
}

// دالة الاختبار التي تحاكي منطق بايثون (assert مع تقريب لرقمين عشريين)
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
        double result = Solution::cubeDiagonal(tests[i].input);
        // نتحقق أن النتيجة تقريبا تساوي المتوقعة مع تقريب 2 خانات عشرية
        assert(almostEqual(result, tests[i].expected) &&
               "Test failed: result differs from expected");
    }
    std::cout << "ALL TESTS PASSED\n";
}

int main() {
    run_tests();
    return 0;
}
