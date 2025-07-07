#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// دالة تنفذ العملية المطلوبة
string calc(double num1, double num2, char op) {
    double result;
    switch (op) {
        case '+': return to_string(num1 + num2);
        case '-': return to_string(num1 - num2);
        case '*': return to_string(num1 * num2);
        case '/':
            if (num2 != 0.0) return to_string(num1 / num2);
            else return "Error: Division by zero";
        default: return "Error: Invalid operator";
    }
}

// تقريب الأعداد العشرية
bool almost_equal(double a, double b, double tol = 1e-6) {
    return fabs(a - b) < tol;
}

// اختبار عدد عشري
void assertFloatEqual(string testName, string result, double expected) {
    try {
        double actual = stod(result);
        if (almost_equal(actual, expected))
            cout << "✅ " << testName << " passed.\n";
        else
            cout << "❌ " << testName << " failed. Expected: " << expected << ", Got: " << actual << "\n";
    } catch (...) {
        cout << "❌ " << testName << " failed (exception parsing float): " << result << "\n";
    }
}

// اختبار قيمة نصية
void assertEqual(string testName, string result, string expected) {
    if (result == expected)
        cout << "✅ " << testName << " passed.\n";
    else
        cout << "❌ " << testName << " failed. Expected: " << expected << ", Got: " << result << "\n";
}

int main() {
    assertFloatEqual("Addition", calc(3, 5, '+'), 8.0);
    assertFloatEqual("Subtraction", calc(10, 4, '-'), 6.0);
    assertFloatEqual("Multiplication", calc(7, 6, '*'), 42.0);
    assertFloatEqual("Division", calc(9, 3, '/'), 3.0);
    assertEqual("Division by Zero", calc(5, 0, '/'), "Error: Division by zero");
    assertEqual("Invalid Operator", calc(5, 3, '^'), "Error: Invalid operator");
    assertFloatEqual("Negative Addition", calc(-3, -7, '+'), -10.0);
    assertFloatEqual("Negative Subtraction", calc(-10, -5, '-'), -5.0);
    assertFloatEqual("Negative Multiplication", calc(-4, 5, '*'), -20.0);
    assertFloatEqual("Negative Division", calc(-10, 2, '/'), -5.0);
    assertFloatEqual("Float Addition", calc(5.5, 2.2, '+'), 7.7);
    assertFloatEqual("Float Multiplication", calc(5.5, 2.2, '*'), 12.1);
    return 0;
}
