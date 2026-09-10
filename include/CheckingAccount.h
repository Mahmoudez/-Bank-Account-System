#ifndef CHECKING_ACCOUNT_H
#define CHECKING_ACCOUNT_H

#include "BankAccount.h"

class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;
    double transactionFee;

    void chargeTransactionFee();

public:
    CheckingAccount(std::string accNum, std::string accHolder, double initialBalance,
                     bool isClosed, double overdraftLimit, double transactionFee);

    bool withdraw(double amount) override;
    std::string getAccountType() const override;
};

#endif // CHECKING_ACCOUNT_H
