#include <iostream>
#include <stdexcept>
#include "../../../source/output/codestral/cpp/Task181_MISTRAL_codestral-latest.cpp"

int main() {
    int passed = 0, total = 7;

    try {
        // Test 1: Deposit to open account
        BankAccount acc1(1000);
        acc1.deposit(500);

        // Test 2: Withdraw valid amount
        if (!acc1.withdraw(300)) {
            std::cout << "Test 2 Failed: valid withdraw failed\n"; return 1;
        }

        // Test 3: Withdraw too much (should fail but not throw)
        if (acc1.withdraw(2000)) {
            std::cout << "Test 3 Failed: over-withdraw succeeded\n"; return 1;
        }

        // Test 4: Deposit negative amount (should throw)
        try {
            acc1.deposit(-100);
            std::cout << "Test 4 Failed: negative deposit didn't throw\n"; return 1;
        } catch (const std::invalid_argument&) {
            passed++;
        }

        // Test 5: Withdraw negative amount (should throw)
        try {
            acc1.withdraw(-100);
            std::cout << "Test 5 Failed: negative withdraw didn't throw\n"; return 1;
        } catch (const std::invalid_argument&) {
            passed++;
        }

        // Test 6: Operations on closed account (should throw)
        acc1.close();
        try {
            acc1.deposit(100);
            std::cout << "Test 6 Failed: deposit on closed account didn't throw\n"; return 1;
        } catch (const std::runtime_error&) {
            passed++;
        }

        // Test 7: Withdraw on closed account (should throw)
        try {
            acc1.withdraw(50);
            std::cout << "Test 7 Failed: withdraw on closed account didn't throw\n"; return 1;
        } catch (const std::runtime_error&) {
            passed++;
        }

        std::cout << "All test cases passed!\n";
    } catch (const std::exception& e) {
        std::cout << "Unexpected exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
