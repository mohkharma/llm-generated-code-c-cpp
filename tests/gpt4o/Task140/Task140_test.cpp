#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// دالة تنفيذ العملية الحسابية
string calculate(double a, double b, char op) {
    double result;
    switch (op) {
        case '+': return to_string(a + b);
        case '-': return to_string(a - b);
        case '*': return to_string(a * b);
        case '/':
            if (b != 0.0) return to_string(a / b);
            else return "Error: Division by zero";
        default:
            return "Error: Invalid operator";
    }
}

// دالة مقارنة للأرقام العشرية بالتقريب
bool almost_equal(double a, double b, double tol = 1e-6) {
    return fabs(a - b) < tol;
}

// دالة اختبار لنتائج رقمية
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

// دالة اختبار لنتائج نصية (للأخطاء)
void assertEqual(string testName, string result, string expected) {
    if (result == expected)
        cout << "✅ " << testName << " passed.\n";
    else
        cout << "❌ " << testName << " failed. Expected: " << expected << ", Got: " << result << "\n";
}

// Main لتشغيل جميع test cases تلقائيًا
int main() {
    assertFloatEqual("Test Addition", calculate(3, 5, '+'), 8.0);
    assertFloatEqual("Test Subtraction", calculate(10, 4, '-'), 6.0);
    assertFloatEqual("Test Multiplication", calculate(7, 6, '*'), 42.0);
    assertFloatEqual("Test Division", calculate(9, 3, '/'), 3.0);
    assertEqual("Test Division by Zero", calculate(5, 0, '/'), "Error: Division by zero");
    assertEqual("Test Invalid Operator", calculate(5, 3, '^'), "Error: Invalid operator");
    assertFloatEqual("Test Negative Addition", calculate(-3, -7, '+'), -10.0);
    assertFloatEqual("Test Negative Subtraction", calculate(-10, -5, '-'), -5.0);
    assertFloatEqual("Test Negative Multiplication", calculate(-4, 5, '*'), -20.0);
    assertFloatEqual("Test Negative Division", calculate(-10, 2, '/'), -5.0);
    assertFloatEqual("Test Float Addition", calculate(5.5, 2.2, '+'), 7.7);
    assertFloatEqual("Test Float Multiplication", calculate(5.5, 2.2, '*'), 12.1); // تقريب

    return 0;
}
