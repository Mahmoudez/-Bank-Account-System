#ifndef BUSINESS_ACCOUNT_H
#define BUSINESS_ACCOUNT_H

#include "BankAccount.h"

class BusinessAccount : public BankAccount {
private:
    double dailyWithdrawalLimit;
    double overdraftLimit;
    double totalWithdrawnToday;

public:
    BusinessAccount(std::string accNum, std::string accHolder, double initialBalance,
                     bool isClosed, double dailyWithdrawalLimit, double overdraftLimit,
                     double totalWithdrawnToday);

    bool withdraw(double amount) override;
    std::string getAccountType() const override;
};

#endif // BUSINESS_ACCOUNT_H
