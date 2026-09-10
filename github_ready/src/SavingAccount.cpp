#include "SavingAccount.h"
#include <iostream>

SavingAccount::SavingAccount(std::string accNum, std::string accHolder, double initialBalance,
                              bool isClosed, double interestRate, double minimumBalance)
    : BankAccount(std::move(accNum), std::move(accHolder), initialBalance, isClosed),
      interestRate(interestRate), minimumBalance(minimumBalance) {
}

bool SavingAccount::withdraw(double amount) {
    if (isClosed) {
        std::cout << "Cannot withdraw: Account is Closed!\n";
        return false;
    }
    if (amount <= 0) {
        std::cout << "Invalid withdrawal amount!\n";
        return false;
    }
    if (balance - amount < minimumBalance) {
        std::cout << "Sorry, balance cannot go below minimum required: $" << minimumBalance << "\n";
        return false;
    } else {
        balance -= amount;
        std::cout << "Withdrawal Successful :)\n";
        transactions.push_back(Transaction("Withdrawal", amount, balance));
        return true;
    }
}

void SavingAccount::applyInterest() {
    if (!isClosed) {
        double addedBalance = balance * interestRate;
        balance += addedBalance;
        transactions.push_back(Transaction("Apply Interest", addedBalance, balance));
        std::cout << "[SUCCESS] Interest applied: +$" << addedBalance << "\n";
    }
}

std::string SavingAccount::getAccountType() const {
    return "Saving Account";
}
