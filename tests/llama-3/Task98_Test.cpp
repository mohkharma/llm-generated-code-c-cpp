#include <iostream>
#include <limits>

int main() {
    int num;
    std::cout << "Enter a number: ";
    if (!(std::cin >> num)) {
        std::cout << "That's not a valid number!" << std::endl;
        std::cout << "Test case result: FAIL" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
        std::cout << "You entered: " << num << std::endl;
        std::cout << "Test case result: PASS" << std::endl;
    }
    return 0;
}
