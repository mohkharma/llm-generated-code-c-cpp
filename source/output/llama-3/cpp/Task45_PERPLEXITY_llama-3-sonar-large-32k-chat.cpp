#include <iostream>
#include <limits>

void runSafeCalculator() {
    double num1, num2;
    char operation;

    // قراءة الرقم الأول
    std::cout << "Enter first number: ";
    while (!(std::cin >> num1)) {
        std::cout << "Error: Invalid input!\n";
        std::cout << "Enter first number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // قراءة الرقم الثاني
    std::cout << "Enter second number: ";
    while (!(std::cin >> num2)) {
        std::cout << "Error: Invalid input!\n";
        std::cout << "Enter second number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // قراءة العملية
    std::cout << "Enter operation (+, -, *, /): ";
    while (!(std::cin >> operation)) {
        std::cout << "Error: Invalid input!\n";
        std::cout << "Enter operation (+, -, *, /): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // تنفيذ العملية
    if (operation == '+') {
        std::cout << "Result: " << num1 + num2 << std::endl;
    } else if (operation == '-') {
        std::cout << "Result: " << num1 - num2 << std::endl;
    } else if (operation == '*') {
        std::cout << "Result: " << num1 * num2 << std::endl;
    } else if (operation == '/') {
        if (num2 != 0) {
            std::cout << "Result: " << num1 / num2 << std::endl;
        } else {
            std::cout << "Error: Division by zero!" << std::endl;
        }
    } else {
        std::cout << "Error: Invalid operation!" << std::endl;
    }
}
