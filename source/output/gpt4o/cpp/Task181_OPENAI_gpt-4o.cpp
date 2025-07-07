#include <iostream>
#include <mutex>

class BankAccount {
    int id;
    int balance;
    std::mutex mtx;
    bool closed;

public:
    BankAccount(int id, int initialBalance) : id(id), balance(initialBalance), closed(false) {}

    std::string deposit(int amount) {
        std::lock_guard<std::mutex> lock(mtx);
        if (closed) {
            return "Account is closed";
        }
        balance += amount;
        return "Balance: " + std::to_string(balance);
    }

    std::string withdraw(int amount) {
        std::lock_guard<std::mutex> lock(mtx);
        if (closed) {
            return "Account is closed";
        }
        if (balance >= amount) {
            balance -= amount;
            return "Balance: " + std::to_string(balance);
        } else {
            return "Insufficient funds";
        }
    }

    std::string close() {
        std::lock_guard<std::mutex> lock(mtx);
        closed = true;
        return "Account closed";
    }
};

