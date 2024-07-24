#include <iostream>

using namespace std;
//compilation error, fixed
double calculate(double a, double b, char operator1) {
    switch (operator1) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            cout << "Invalid operator" << endl;
            return 0;
    }
}

int main() {
    double a, b;
    // error: expected type-specifier before ';' token
    // char operator;
    char operator1;

    cout << "Enter first number: ";
    cin >> a;

    cout << "Enter second number: ";
    cin >> b;

    cout << "Enter operator (+, -, *, /): ";
    cin >> operator1;

    cout << "Result: " << calculate(a, b, operator1) << endl;

    return 0;
}