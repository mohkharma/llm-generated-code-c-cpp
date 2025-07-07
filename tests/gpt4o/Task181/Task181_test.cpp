#include <iostream>
#include <string>
#include "../../../source/output/gpt4o/cpp/Task181_OPENAI_gpt-4o.cpp"

int main() {
    int passed = 0;
    const int total = 6;

    BankAccount acc(1, 100);

    // Test 1: Deposit 50 → should be 150
    if (acc.deposit(50) != "Balance: 150") {
        std::cout << "Test 1 Failed: Deposit 50\n"; return 1;
    } passed++;

    // Test 2: Withdraw 30 → should be 120
    if (acc.withdraw(30) != "Balance: 120") {
        std::cout << "Test 2 Failed: Withdraw 30\n"; return 1;
    } passed++;

    // Test 3: Withdraw 200 → insufficient funds
    if (acc.withdraw(200) != "Insufficient funds") {
        std::cout << "Test 3 Failed: Over-withdraw\n"; return 1;
    } passed++;

    // Test 4: Close account → expect "Account closed"
    if (acc.close() != "Account closed") {
        std::cout << "Test 4 Failed: Close account\n"; return 1;
    } passed++;

    // Test 5: Deposit after close → expect "Account is closed"
    if (acc.deposit(10) != "Account is closed") {
        std::cout << "Test 5 Failed: Deposit after close\n"; return 1;
    } passed++;

    // Test 6: Withdraw after close → expect "Account is closed"
    if (acc.withdraw(10) != "Account is closed") {
        std::cout << "Test 6 Failed: Withdraw after close\n"; return 1;
    } passed++;

    std::cout << "All " << passed << " test cases passed!\n";
    return 0;
}
