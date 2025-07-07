#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mainProgram() {
    int num1, num2;
    std::cout << "Enter first number: ";
    std::cin >> num1;
    std::cout << "Enter second number: ";
    std::cin >> num2;
    int result = gcd(num1, num2);
    std::cout << "The GCD of " << num1 << " and " << num2 << " is " << result << std::endl;
    return 0;
}

std::string normalize(const std::string& str) {
    std::string res = str;
    res.erase(std::remove(res.begin(), res.end(), '\r'), res.end());
    return res;
}

void runTest(int a, int b, int expected) {
    std::stringstream input;
    input << a << "\n" << b << "\n";

    std::stringstream output;

    auto cinBuf = std::cin.rdbuf();
    auto coutBuf = std::cout.rdbuf();

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    mainProgram();

    std::cin.rdbuf(cinBuf);
    std::cout.rdbuf(coutBuf);

    std::string expectedOutput = "Enter first number: Enter second number: The GCD of "
                                + std::to_string(a) + " and " + std::to_string(b) + " is "
                                + std::to_string(expected) + "\n";
    std::string actualOutput = output.str();

    if (normalize(actualOutput) != normalize(expectedOutput)) {
        std::cerr << "❌ Test failed\n";
        std::cerr << "Input: " << a << ", " << b << "\n";
        std::cerr << "Expected: " << expectedOutput;
        std::cerr << "Actual:   " << actualOutput;
        assert(false);
    }
}

int main() {
    runTest(48, 18, 6);
    runTest(7, 7, 7);
    runTest(0, 15, 15);
    runTest(15, 0, 15);
    runTest(13, 17, 1);
    runTest(1, 25, 1);
    runTest(25, 1, 1);
    runTest(-48, -18, -6);
    runTest(-48, 18, 6);
    runTest(48, -18, -6);
    runTest(123456, 7890, 6);
    runTest(35, 64, 1);
    runTest(7, 1001, 7);
    runTest(1000000, 1000000, 1000000);

    std::cout << "\n✅ All test cases passed.\n";
    return 0;
}
