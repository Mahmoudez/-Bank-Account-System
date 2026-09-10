#include "BusinessAccount.h"
#include <iostream>

BusinessAccount::BusinessAccount(std::string accNum, std::string accHolder, double initialBalance,
                                  bool isClosed, double dailyWithdrawalLimit, double overdraftLimit,
                                  double totalWithdrawnToday)
    : BankAccount(std::move(accNum), std::move(accHolder), initialBalance, isClosed),
      dailyWithdrawalLimit(dailyWithdrawalLimit), overdraftLimit(overdraftLimit),
      totalWithdrawnToday(totalWithdrawnToday) {
}

bool BusinessAccount::withdraw(double amount) {
    if (isClosed) {
        std::cout << "Cannot withdraw: Account is Closed!\n";
        return false;
    }
    if (amount <= 0) {
        std::cout << "Invalid withdrawal amount!\n";
        return false;
    }
    if (balance + overdraftLimit < amount) {
        std::cout << "[ERROR] Cannot withdraw: Exceeds available balance + overdraft limit!\n";
        return false;
    }
    if (totalWithdrawnToday + amount > dailyWithdrawalLimit) {
        std::cout << "[ERROR] Cannot withdraw: Exceeds daily withdrawal limit!\n";
        return false;
    }

    balance -= amount;
    totalWithdrawnToday += amount;
    transactions.push_back(Transaction("Business Withdrawal", amount, balance));
    std::cout << "[SUCCESS] Withdrawal success\n";
    return true;
}

std::string BusinessAccount::getAccountType() const {
    return "Business Account";
}
