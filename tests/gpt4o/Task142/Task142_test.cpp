#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>

extern "C" {
    int gcd(int a, int b);
}

int mainProgram() {
    int a, b;
    std::cout << "Enter first number: ";
    std::cin >> a;
    std::cout << "Enter second number: ";
    std::cin >> b;
    std::cout << "Greatest Common Divisor: " << gcd(a, b) << std::endl;
    return 0;
}

extern "C" int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
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

    std::string expectedOutput = "Enter first number: Enter second number: Greatest Common Divisor: " + std::to_string(expected) + "\n";
    std::string actualOutput = output.str();

    if (normalize(actualOutput) != normalize(expectedOutput)) {
        std::cerr << "❌ Test failed\n";
        std::cerr << "Input: " << a << ", " << b << "\n";
        std::cerr << "Expected: '" << expectedOutput << "'\n";
        std::cerr << "Actual:   '" << actualOutput << "'\n";
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
