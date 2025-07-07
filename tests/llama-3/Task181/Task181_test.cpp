#include <iostream>
#include "../../../source/output/llama-3/cpp/Task181_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

int main() {
    int passed = 0;
    const int total = 7;

    BankAccount acc(100.0);

    // Test 1: Deposit 50 → should succeed
    if (!acc.deposit(50)) {
        std::cout << "Test 1 Failed: deposit(50) failed\n"; return 1;
    } passed++;

    // Test 2: Withdraw 30 → should succeed
    if (!acc.withdraw(30)) {
        std::cout << "Test 2 Failed: withdraw(30) failed\n"; return 1;
    } passed++;

    // Test 3: Balance should be 120
    double bal = acc.getBalance();
    if (bal != 120.0) {
        std::cout << "Test 3 Failed: Expected balance 120, got " << bal << "\n"; return 1;
    } passed++;

    // Test 4: Withdraw 200 → should fail (not enough)
    if (acc.withdraw(200)) {
        std::cout << "Test 4 Failed: withdraw(200) should fail\n"; return 1;
    } passed++;

    // Test 5: Close account and try deposit → should fail
    acc.closeAccount();
    if (acc.deposit(10)) {
        std::cout << "Test 5 Failed: deposit after close should fail\n"; return 1;
    } passed++;

    // Test 6: Withdraw after close → should fail
    if (acc.withdraw(10)) {
        std::cout << "Test 6 Failed: withdraw after close should fail\n"; return 1;
    } passed++;

    // Test 7: Reopen account and deposit → should succeed
    acc.openAccount();
    if (!acc.deposit(80)) {
        std::cout << "Test 7 Failed: deposit after reopen failed\n"; return 1;
    } passed++;

    std::cout << "All " << passed << " test cases passed!\n";
    return 0;
}
