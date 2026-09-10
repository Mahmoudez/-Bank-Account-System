#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>
#include <memory>
#include "BankAccount.h"
#include "SavingAccount.h"
#include "CheckingAccount.h"
#include "BusinessAccount.h"
#include "LoanAccount.h"

class Bank {
private:
    std::string bankName;
    int nextAccountNumber;
    std::vector<std::unique_ptr<BankAccount>> bankAccounts;

    std::string genAccountNumber(const std::string &prefix);

public:
    Bank(std::string name, int nextAccountNumber = 1000);

    SavingAccount* createSavingAccount(std::string holder, double initialBalance,
                                        double interestRate, double minimumBalance);
    CheckingAccount* createCheckingAccount(std::string holder, double initialBalance,
                                            double overdraftLimit, double transactionFee);
    BusinessAccount* createBusinessAccount(std::string holder, double initialBalance,
                                            double dailyWithdrawalLimit, double overdraftLimit,
                                            double totalWithdrawnToday);
    LoanAccount* createLoanAccount(std::string holder, double initialBalance,
                                    double originalLoanAmount, double interestRate,
                                    double monthlyInstallment);

    BankAccount* findAccount(const std::string &accNum);
    double getTotalBankBalance() const;
    void displayAllAccounts() const;

    // Transfers `amount` from one account to another. Returns false (and leaves
    // both accounts untouched) if the withdrawal from `from` fails.
    bool executeTransfer(BankAccount *from, BankAccount *to, double amount);
};

#endif // BANK_H
