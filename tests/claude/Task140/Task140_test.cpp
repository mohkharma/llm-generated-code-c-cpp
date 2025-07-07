#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// دالة تنفذ العملية الحسابية المطلوبة وتعاد النتيجة كسلسلة نصية
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

// دالة لمقارنة الأرقام العشرية بشكل تقريبي
bool almost_equal(double a, double b, double tol = 1e-9) {
    return fabs(a - b) < tol;
}

// دالة اختبار لمقارنة النتائج النصية
void assertEqual(string testName, string result, string expected) {
    if (result == expected) {
        cout << "✅ " << testName << " passed." << endl;
    } else {
        cout << "❌ " << testName << " failed. Expected: " << expected << ", Got: " << result << endl;
    }
}

// دالة اختبار لمقارنة نتائج عائمة
void assertFloatEqual(string testName, string result, double expected) {
    double res = stod(result);
    if (almost_equal(res, expected)) {
        cout << "✅ " << testName << " passed." << endl;
    } else {
        cout << "❌ " << testName << " failed. Expected: " << expected << ", Got: " << res << endl;
    }
}

// Main يحتوي جميع اختبارات البايثون نفسها
int main() {
    assertFloatEqual("Addition", calc(3, 5, '+'), 8.0);
    assertFloatEqual("Subtraction", calc(10, 4, '-'), 6.0);
    assertFloatEqual("Multiplication", calc(7, 6, '*'), 42.0);
    assertFloatEqual("Division", calc(9, 3, '/'), 3.0);
    assertEqual("Division by zero", calc(5, 0, '/'), "Error: Division by zero");
    assertEqual("Invalid operator", calc(5, 3, '^'), "Error: Invalid operator");
    assertFloatEqual("Negative Addition", calc(-3, -7, '+'), -10.0);
    assertFloatEqual("Negative Subtraction", calc(-10, -5, '-'), -5.0);
    assertFloatEqual("Negative Multiplication", calc(-4, 5, '*'), -20.0);
    assertFloatEqual("Negative Division", calc(-10, 2, '/'), -5.0);
    assertFloatEqual("Float Addition", calc(5.5, 2.2, '+'), 7.7);
    assertFloatEqual("Float Multiplication", calc(5.5, 2.2, '*'), 12.1);  // ناتج تقريبي
    return 0;
}
