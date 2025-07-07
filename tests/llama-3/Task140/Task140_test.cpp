#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// دالة منفصلة تنفذ العملية وترجع النتيجة
string calc(double num1, double num2, char op) {
    if (op == '+') return to_string(num1 + num2);
    else if (op == '-') return to_string(num1 - num2);
    else if (op == '*') return to_string(num1 * num2);
    else if (op == '/') {
        if (num2 != 0.0) return to_string(num1 / num2);
        else return "Error Division by zero is not allowed.";
    } else {
        return "Invalid operator. Please enter either +, -, * or /.";
    }
}

// اختبار رقمي
void assertFloatEqual(string name, string result, double expected) {
    try {
        double actual = stod(result);
        if (fabs(actual - expected) < 1e-6)
            cout << "✅ " << name << " passed.\n";
        else
            cout << "❌ " << name << " failed. Expected: " << expected << ", Got: " << actual << endl;
    } catch (...) {
        cout << "❌ " << name << " failed. Result was not a number: " << result << endl;
    }
}

// اختبار نصي
void assertEqual(string name, string result, string expected) {
    if (result == expected)
        cout << "✅ " << name << " passed.\n";
    else
        cout << "❌ " << name << " failed. Expected: " << expected << ", Got: " << result << endl;
}

int main() {
    assertFloatEqual("Addition", calc(3, 5, '+'), 8.0);
    assertFloatEqual("Subtraction", calc(10, 4, '-'), 6.0);
    assertFloatEqual("Multiplication", calc(7, 6, '*'), 42.0);
    assertFloatEqual("Division", calc(9, 3, '/'), 3.0);
    assertEqual("Division by Zero", calc(5, 0, '/'), "Error Division by zero is not allowed.");
    assertEqual("Invalid Operator", calc(5, 3, '^'), "Invalid operator. Please enter either +, -, * or /.");
    assertFloatEqual("Negative Addition", calc(-3, -7, '+'), -10.0);
    assertFloatEqual("Negative Subtraction", calc(-10, -5, '-'), -5.0);
    assertFloatEqual("Negative Multiplication", calc(-4, 5, '*'), -20.0);
    assertFloatEqual("Negative Division", calc(-10, 2, '/'), -5.0);
    assertFloatEqual("Float Addition", calc(5.5, 2.2, '+'), 7.7);
    assertFloatEqual("Float Multiplication", calc(5.5, 2.2, '*'), 12.1);

    return 0;
}
