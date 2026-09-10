#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

class BankAccount {
protected:
    std::string accountNumber;
    std::string accountHolder;
    double balance;
    std::vector<Transaction> transactions;
    bool isClosed;

public:
    BankAccount(std::string accNum, std::string accHolder, double initialBalance, bool isClosed = false);

    void deposit(double amount);
    virtual bool withdraw(double amount);

    // Getters
    std::string getAccountNumber() const;
    double getBalance() const;
    virtual std::string getAccountType() const;

    virtual void getAccountInfo() const;
    virtual bool closeAccount();
    virtual void displayTransactionHistory();

    virtual ~BankAccount() = default;
};

#endif // BANK_ACCOUNT_H
