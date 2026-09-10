#include "BankAccount.h"
#include <iomanip>
#include <iostream>

BankAccount::BankAccount(std::string accNum, std::string accHolder, double initialBalance, bool isClosed)
    : accountNumber(std::move(accNum)), accountHolder(std::move(accHolder)),
      balance(initialBalance), isClosed(isClosed) {
    transactions.push_back(Transaction("Account Opened", initialBalance, initialBalance));
}

void BankAccount::deposit(double amount) {
    if (amount > 0 && !isClosed) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount, balance));
    } else {
        std::cout << "Error: Invalid amount or Account is Closed!\n";
    }
}

bool BankAccount::withdraw(double amount) {
    if (amount <= balance && !isClosed) {
        balance -= amount;
        std::cout << "Withdrawal Successful :)\n";
        transactions.push_back(Transaction("Withdrawal", amount, balance));
        return true;
    } else {
        std::cout << "Sorry, there isn't enough balance ):\n";
        return false;
    }
}

std::string BankAccount::getAccountNumber() const { return accountNumber; }

double BankAccount::getBalance() const { return balance; }

std::string BankAccount::getAccountType() const {
    return "Standard Account";
}

void BankAccount::getAccountInfo() const {
    std::cout << "\n==================================================\n"
               << "                 ACCOUNT SUMMARY                  \n"
               << "==================================================\n";
    std::cout << std::left << std::setw(20) << "Account Number:" << getAccountNumber() << "\n";
    std::cout << std::left << std::setw(20) << "Account Holder:" << accountHolder << "\n";
    std::cout << std::left << std::setw(20) << "Account Type:" << getAccountType() << "\n";
    std::cout << std::left << std::setw(20) << "Account State:" << (isClosed ? "Closed" : "Open") << "\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << std::left << std::setw(20) << "Account Balance:"
               << "$" << std::fixed << std::setprecision(2) << getBalance() << "\n";
    std::cout << "==================================================\n\n";
}

bool BankAccount::closeAccount() {
    if (balance != 0) {
        std::cout << "Error: Your balance must be 0.00 to close. Please withdraw all your balance.\n";
        return false;
    } else {
        isClosed = true;
        std::cout << "[SUCCESS] Your account has been closed.\n";
        return true;
    }
}

void BankAccount::displayTransactionHistory() {
    std::cout << "\n     ======= Transaction History =======\n";
    std::cout << "     ======= for account " << accountHolder << " =======\n";
    for (auto &tran : transactions) {
        tran.displayTransaction();
    }
}
