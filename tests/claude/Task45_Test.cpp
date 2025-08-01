#include "../../source/output/claude/cpp/Task45_CLAUDE_claude-3-5-sonnet-20240620.cpp"
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

int testsPassed = 0;
int testsFailed = 0;

void printResult(const std::string& testName, bool passed) {
    if (passed) {
        std::cout << "[PASS] " << testName << "\n";
        testsPassed++;
    } else {
        std::cout << "[FAIL] " << testName << "\n";
        testsFailed++;
    }
}

// بدل استدعاء main، نحاكي السلوك مباشرة هنا
void simulateMainBehavior(const std::string& inputStr, std::string& output) {
    std::stringstream input(inputStr);
    std::stringstream buffer;

    std::streambuf* oldCin = std::cin.rdbuf();
    std::streambuf* oldCout = std::cout.rdbuf();

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(buffer.rdbuf());

    try {
        double a, b;
        std::cout << "Enter first number: ";
        if (!(std::cin >> a)) {
            throw std::invalid_argument("Invalid input");
        }

        std::cout << "Enter second number: ";
        if (!(std::cin >> b)) {
            throw std::invalid_argument("Invalid input");
        }

        double result = divide_numbers(a, b);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::invalid_argument&) {
        std::cout << "Error: Please enter valid numbers." << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << "Program execution completed." << std::endl;

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);
    output = buffer.str();
}

int main() {
    // test_divide_numbers_valid
    try {
        bool pass = divide_numbers(10, 2) == 5 &&
                    divide_numbers(-10, 2) == -5 &&
                    divide_numbers(0, 1) == 0;
        printResult("test_divide_numbers_valid", pass);
    } catch (...) {
        printResult("test_divide_numbers_valid", false);
    }

    // test_divide_numbers_zero_division
    try {
        divide_numbers(10, 0);
        printResult("test_divide_numbers_zero_division", false);
    } catch (const std::exception&) {
        printResult("test_divide_numbers_zero_division", true);
    }

    // test_divide_numbers_invalid_input
    try {
        divide_numbers(std::stod("x"), std::stod("2"));
        printResult("test_divide_numbers_invalid_input", false);
    } catch (...) {
        printResult("test_divide_numbers_invalid_input", true);
    }

    // simulateMainBehavior tests
    {
        std::string output;
        simulateMainBehavior("10\n2\n", output);
        bool pass = output.find("Result: 5") != std::string::npos &&
                    output.find("Program execution completed.") != std::string::npos;
        printResult("test_main_valid_input", pass);
    }

    {
        std::string output;
        simulateMainBehavior("10\n0\n", output);
        bool pass = output.find("Error: Cannot divide by zero.") != std::string::npos &&
                    output.find("Program execution completed.") != std::string::npos;
        printResult("test_main_zero_division", pass);
    }

    {
        std::string output;
        simulateMainBehavior("a\n2\n", output);
        bool pass = output.find("Error: Please enter valid numbers.") != std::string::npos &&
                    output.find("Program execution completed.") != std::string::npos;
        printResult("test_main_invalid_input", pass);
    }

    {
        std::string output;
        simulateMainBehavior("10\n2\n", output);
        bool pass = output.find("Result: 5") != std::string::npos &&
                    output.find("Program execution completed.") != std::string::npos;
        printResult("test_main_with_invalid_input", pass);
    }

    {
        std::string output;
        simulateMainBehavior("-10\n2\n", output);
        bool pass = output.find("Result: -5") != std::string::npos &&
                    output.find("Program execution completed.") != std::string::npos;
        printResult("test_main_negative_numbers", pass);
    }

    {
        std::string output;
        simulateMainBehavior("0\n1\n", output);
        bool pass = output.find("Result: 0") != std::string::npos &&
                    output.find("Program execution completed.") != std::string::npos;
        printResult("test_main_zero_numerator", pass);
    }

    {
        std::string allOutput;
        for (int i = 0; i < 10; ++i) {
            std::string output;
            simulateMainBehavior("10\n2\n", output);
            allOutput += output;
        }
        bool pass = allOutput.find("Result: 5") != std::string::npos &&
                    allOutput.find("Program execution completed.") != std::string::npos;
        printResult("test_main_valid_input_multiple_times", pass);
    }

    {
        std::string output;
        simulateMainBehavior("1\n0\n", output);
        bool pass = output.find("Error: Cannot divide by zero.") != std::string::npos &&
                    output.find("Program execution completed.") != std::string::npos;
        printResult("test_main_small_numbers_zero_division", pass);
    }

    // Summary
    std::cout << "\nTests passed: " << testsPassed << "\n";
    std::cout << "Tests failed: " << testsFailed << "\n";

    return testsFailed == 0 ? 0 : 1;
}
