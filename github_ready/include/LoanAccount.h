#ifndef LOAN_ACCOUNT_H
#define LOAN_ACCOUNT_H

#include "BankAccount.h"

class LoanAccount : public BankAccount {
private:
    double originalLoanAmount;
    double interestRate;
    double monthlyInstallment;

public:
    LoanAccount(std::string accNum, std::string accHolder, double initialBalance,
                bool isClosed, double originalLoanAmount, double interestRate,
                double monthlyInstallment);

    bool withdraw(double amount) override; // disabled: loans can't be withdrawn from
    bool payInstallment(double amount);
    void applyInterestRate();
    std::string getAccountType() const override;
};

#endif // LOAN_ACCOUNT_H
