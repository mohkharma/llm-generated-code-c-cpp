#include <iostream>
#include <limits>

void readAndSquareNumber() {
    std::cout << "Enter a number: ";
    int number;

    while (!(std::cin >> number)) {
        std::cout << "Invalid input. Please enter a number." << std::endl;
        std::cin.clear(); // مسح حالة الخطأ
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // تجاهل السطر الحالي
    }

    std::cout << "You entered: " << number << std::endl;

    int squared = number * number;
    std::cout << "Square of the number: " << squared << std::endl;
}
