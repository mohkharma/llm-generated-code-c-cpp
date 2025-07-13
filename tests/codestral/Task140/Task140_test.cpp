#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// دالة الحساب
string calc(double num1, double num2, char op) {
    double result;
    switch (op) {
        case '+':
            result = num1 + num2;
            return to_string(result);
        case '-':
            result = num1 - num2;
            return to_string(result);
        case '*':
            result = num1 * num2;
            return to_string(result);
        case '/':
            if (num2 != 0.0) {
                result = num1 / num2;
                return to_string(result);
            } else {
                return "Error: Division by zero";
            }
        default:
            return "Error: Invalid operator";
    }
}

// مقارنة أرقام عشرية بتقريب
bool almost_equal(double a, double b, double tol = 1e-6) {
    return fabs(a - b) < tol;
}

// طباعة نتيجة اختبار لأرقام عشرية
void assertFloatEqual(string testName, string result, double expected) {
    double actual;
    try {
        actual = stod(result);
    } catch (...) {
        cout << "❌ " << testName << " failed. Expected float: " << expected << ", but got: " << result << endl;
        return;
    }

    if (almost_equal(actual, expected)) {
        cout << "✅ " << testName << " passed." << endl;
    } else {
        cout << "❌ " << testName << " failed. Expected: " << expected << ", Got: " << actual << endl;
    }
}

// طباعة نتيجة اختبار نصي
void assertEqual(string testName, string result, string expected) {
    if (result == expected) {
        cout << "✅ " << testName << " passed." << endl;
    } else {
        cout << "❌ " << testName << " failed. Expected: " << expected << ", Got: " << result << endl;
    }
}

int main() {
    // Test cases بناءً على Python tests
    assertFloatEqual("Test Addition", calc(3, 5, '+'), 8.0);
    assertFloatEqual("Test Subtraction", calc(10, 4, '-'), 6.0);
    assertFloatEqual("Test Multiplication", calc(7, 6, '*'), 42.0);
    assertFloatEqual("Test Division", calc(9, 3, '/'), 3.0);
    assertEqual("Test Division by Zero", calc(5, 0, '/'), "Error: Division by zero");
    assertEqual("Test Invalid Operator", calc(5, 3, '^'), "Error: Invalid operator");
    assertFloatEqual("Test Negative Addition", calc(-3, -7, '+'), -10.0);
    assertFloatEqual("Test Negative Subtraction", calc(-10, -5, '-'), -5.0);
    assertFloatEqual("Test Negative Multiplication", calc(-4, 5, '*'), -20.0);
    assertFloatEqual("Test Negative Division", calc(-10, 2, '/'), -5.0);
    assertFloatEqual("Test Float Addition", calc(5.5, 2.2, '+'), 7.7);
    assertFloatEqual("Test Float Multiplication", calc(5.5, 2.2, '*'), 12.1); // تقريب

    return 0;
}
