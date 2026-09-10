#include "CheckingAccount.h"
#include <iostream>

CheckingAccount::CheckingAccount(std::string accNum, std::string accHolder, double initialBalance,
                                  bool isClosed, double overdraftLimit, double transactionFee)
    : BankAccount(std::move(accNum), std::move(accHolder), initialBalance, isClosed),
      overdraftLimit(overdraftLimit), transactionFee(transactionFee) {
}

void CheckingAccount::chargeTransactionFee() {
    balance -= transactionFee;
    transactions.push_back(Transaction("Charge Transaction Fee", transactionFee, balance));
}

bool CheckingAccount::withdraw(double amount) {
    double totalDeduction = amount + transactionFee;
    if (isClosed) {
        std::cout << "Cannot withdraw: Account is Closed!\n";
        return false;
    }
    if (amount <= 0) {
        std::cout << "Invalid withdrawal amount!\n";
        return false;
    }
    if ((balance + overdraftLimit) >= totalDeduction) {
        balance -= amount;
        std::cout << "Withdrawal Successful :)\n";
        transactions.push_back(Transaction("Withdrawal", amount, balance));
        chargeTransactionFee();
        return true;
    } else {
        std::cout << "[ERROR] Transaction failed: Exceeds overdraft limit!\n";
        return false;
    }
}

std::string CheckingAccount::getAccountType() const {
    return "Checking Account";
}
