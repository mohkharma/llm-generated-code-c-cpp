#include <iostream>
#include <string>
#include "../../../source/output/claude/cpp/Task181_CLAUDE_claude-3-5-sonnet-20240620.cpp"

int main() {
    Bank bank;

    // Test 1: Open a new account
    if (!bank.openAccount("12345", 1000)) {
        std::cout << "Test 1 Failed: openAccount failed\n"; return 1;
    }

    // Test 2: Open the same account again (should fail)
    if (bank.openAccount("12345", 0)) {
        std::cout << "Test 2 Failed: duplicate openAccount succeeded\n"; return 1;
    }

    // Test 3: Deposit money into the account
    if (!bank.deposit("12345", 500)) {
        std::cout << "Test 3 Failed: deposit failed\n"; return 1;
    }

    // Test 4: Withdraw money from the account
    if (!bank.withdraw("12345", 200)) {
        std::cout << "Test 4 Failed: withdraw failed\n"; return 1;
    }

    // Test 5: Withdraw more money than available (should fail)
    if (bank.withdraw("12345", 2000)) {
        std::cout << "Test 5 Failed: over-withdraw succeeded\n"; return 1;
    }

    // Test 6: Close the account
    if (!bank.closeAccount("12345")) {
        std::cout << "Test 6 Failed: closeAccount failed\n"; return 1;
    }

    // Test 7: Deposit into closed account (should fail)
    if (bank.deposit("12345", 500)) {
        std::cout << "Test 7 Failed: deposit into closed account succeeded\n"; return 1;
    }

    // Test 8: Withdraw from closed account (should fail)
    if (bank.withdraw("12345", 200)) {
        std::cout << "Test 8 Failed: withdraw from closed account succeeded\n"; return 1;
    }

    // Test 9: Close the same account again (should fail)
    if (bank.closeAccount("12345")) {
        std::cout << "Test 9 Failed: double closeAccount succeeded\n"; return 1;
    }

    // Test 10: Open another account
    if (!bank.openAccount("67890", 1500)) {
        std::cout << "Test 10 Failed: openAccount for 67890 failed\n"; return 1;
    }

    BankAccount* acc = bank.getAccount("67890");
    if (!acc || acc->getBalance() != 1500) {
        std::cout << "Test 10 Failed: balance check failed\n"; return 1;
    }

    std::cout << "All test cases passed!\n";
    return 0;
}
