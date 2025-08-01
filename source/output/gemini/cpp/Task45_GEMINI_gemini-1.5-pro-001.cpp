#include <iostream>
#include <limits>

using namespace std;

int getIntegerInput(const string& prompt) {
    while (true) {
        int input;
        cout << prompt;
        if (cin >> input) {
            return input;
        } else {
            cout << "Invalid input. Please enter an integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

double performOperation(int choice, int num1, int num2) {
    switch (choice) {
        case 1:
            return num1 + num2;
        case 2:
            return num1 - num2;
        case 3:
            return num1 * num2;
        case 4:
            if (num2 == 0) {
                throw runtime_error("Cannot divide by zero.");
            }
            return static_cast<double>(num1) / num2;
        default:
            throw invalid_argument("Invalid choice.");
    }
}
