#ifndef SAVING_ACCOUNT_H
#define SAVING_ACCOUNT_H

#include "BankAccount.h"

class SavingAccount : public BankAccount {
private:
    double interestRate;
    double minimumBalance;

public:
    SavingAccount(std::string accNum, std::string accHolder, double initialBalance,
                  bool isClosed, double interestRate, double minimumBalance);

    bool withdraw(double amount) override;
    void applyInterest();
    std::string getAccountType() const override;
};

#endif // SAVING_ACCOUNT_H
