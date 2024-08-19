#include <iostream>

int main() {
    double num1, num2;
    //error: expected type-specifier before ‘;’ token
    // char operator;
    char operator1;

    std::cout << "Enter first number: ";
    std::cin >> num1;

    std::cout << "Enter second number: ";
    std::cin >> num2;

    std::cout << "Enter operator (+, -, *, /): ";
    std::cin >> operator1;

    double result;

    switch (operator1) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                std::cout << "Error: Division by zero" << std::endl;
                return 0;
            }
            break;
        default:
            std::cout << "Error: Invalid operator" << std::endl;
            return 0;
    }

    std::cout << "Result: " << result << std::endl;

    return 0;
}