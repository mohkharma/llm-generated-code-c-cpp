#include <iostream>
#include "../../../source/output/gemini/cpp/Task181_GEMINI_gemini-1.5-pro-001.cpp"

int main() {
    int passed = 0;
    const int total = 9;

    try {
        BankAccount acc(1000);

        // Test 1: deposit valid amount
        acc.deposit(500);
        passed++;

        // Test 2: withdraw valid amount
        acc.withdraw(200);
        passed++;

        // Test 3: get balance
        double bal = acc.getBalance();
        if (bal != 1300) {
            std::cout << "Test 3 Failed: Expected 1300, got " << bal << "\n";
            return 1;
        }
        passed++;

        // Test 4: withdraw more than balance -> exception
        try {
            acc.withdraw(2000);
            std::cout << "Test 4 Failed: Over-withdraw didn't throw\n";
            return 1;
        } catch (const std::runtime_error&) {
            passed++;
        }

        // Test 5: deposit negative -> exception
        try {
            acc.deposit(-100);
            std::cout << "Test 5 Failed: Negative deposit didn't throw\n";
            return 1;
        } catch (const std::invalid_argument&) {
            passed++;
        }

        // Test 6: withdraw negative -> exception
        try {
            acc.withdraw(-50);
            std::cout << "Test 6 Failed: Negative withdraw didn't throw\n";
            return 1;
        } catch (const std::invalid_argument&) {
            passed++;
        }

        // Test 7: close account
        acc.close();
        passed++;

        // Test 8: get balance after closing -> exception
        try {
            acc.getBalance();
            std::cout << "Test 8 Failed: getBalance on closed account didn't throw\n";
            return 1;
        } catch (const std::runtime_error&) {
            passed++;
        }

        // Test 9: open account again (should succeed)
        acc.open();
        passed++;

        std::cout << "All " << passed << " test cases passed!\n";
        return 0;

    } catch (const std::exception& e) {
        std::cout << "Unexpected exception: " << e.what() << "\n";
        return 1;
    }
}
