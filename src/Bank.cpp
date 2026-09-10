#include "Bank.h"
#include <iostream>

Bank::Bank(std::string name, int nextAccountNumber)
    : bankName(std::move(name)), nextAccountNumber(nextAccountNumber) {
}

std::string Bank::genAccountNumber(const std::string &prefix) {
    return prefix + "-" + std::to_string(++nextAccountNumber);
}

SavingAccount* Bank::createSavingAccount(std::string holder, double initialBalance,
                                          double interestRate, double minimumBalance) {
    std::string accNum = genAccountNumber("SAV");
    auto sav = std::make_unique<SavingAccount>(accNum, holder, initialBalance, false,
                                                interestRate, minimumBalance);
    SavingAccount *rawPtr = sav.get();
    bankAccounts.push_back(std::move(sav));
    std::cout << "[SUCCESS] Saving Account created for " << holder << " with ID: " << accNum << "\n";
    return rawPtr;
}

CheckingAccount* Bank::createCheckingAccount(std::string holder, double initialBalance,
                                              double overdraftLimit, double transactionFee) {
    std::string accNum = genAccountNumber("CHK");
    auto chk = std::make_unique<CheckingAccount>(accNum, holder, initialBalance, false,
                                                  overdraftLimit, transactionFee);
    CheckingAccount *rawPtr = chk.get();
    bankAccounts.push_back(std::move(chk));
    std::cout << "[SUCCESS] Checking Account created for " << holder << " with ID: " << accNum << "\n";
    return rawPtr;
}

BusinessAccount* Bank::createBusinessAccount(std::string holder, double initialBalance,
                                              double dailyWithdrawalLimit, double overdraftLimit,
                                              double totalWithdrawnToday) {
    std::string accNum = genAccountNumber("BUS");
    auto bus = std::make_unique<BusinessAccount>(accNum, holder, initialBalance, false,
                                                  dailyWithdrawalLimit, overdraftLimit,
                                                  totalWithdrawnToday);
    BusinessAccount *rawPtr = bus.get();
    bankAccounts.push_back(std::move(bus));
    std::cout << "[SUCCESS] Business Account created for " << holder << " with ID: " << accNum << "\n";
    return rawPtr;
}

LoanAccount* Bank::createLoanAccount(std::string holder, double initialBalance,
                                      double originalLoanAmount, double interestRate,
                                      double monthlyInstallment) {
    std::string accNum = genAccountNumber("LON");
    auto loan = std::make_unique<LoanAccount>(accNum, holder, initialBalance, false,
                                               originalLoanAmount, interestRate,
                                               monthlyInstallment);
    LoanAccount *rawPtr = loan.get();
    bankAccounts.push_back(std::move(loan));
    std::cout << "[SUCCESS] Loan Account created for " << holder << " with ID: " << accNum << "\n";
    return rawPtr;
}

BankAccount* Bank::findAccount(const std::string &accNum) {
    for (auto &acc : bankAccounts) {
        if (acc->getAccountNumber() == accNum) {
            std::cout << "[SUCCESS] The account is on the system.\n";
            return acc.get();
        }
    }
    std::cout << "[ERROR] The account is not defined.\n";
    return nullptr;
}

double Bank::getTotalBankBalance() const {
    double total = 0;
    for (const auto &account : bankAccounts) {
        total += account->getBalance();
    }
    return total;
}

void Bank::displayAllAccounts() const {
    if (bankAccounts.empty()) {
        std::cout << "[INFO] No accounts currently registered in the bank system.\n";
        return;
    }

    std::cout << "\n==================================================\n";
    std::cout << "        TOTAL REGISTERED ACCOUNTS: " << bankAccounts.size() << "\n";
    std::cout << "==================================================\n";

    for (const auto &acc : bankAccounts) {
        acc->getAccountInfo();
    }
}

bool Bank::executeTransfer(BankAccount *from, BankAccount *to, double amount) {
    if (from == nullptr || to == nullptr) {
        std::cout << "[ERROR] Transfer failed: invalid account(s).\n";
        return false;
    }
    if (from == to) {
        std::cout << "[ERROR] Transfer failed: source and destination are the same account.\n";
        return false;
    }
    if (amount <= 0) {
        std::cout << "[ERROR] Transfer failed: invalid amount.\n";
        return false;
    }

    // withdraw() is polymorphic, so each account type's own rules
    // (overdraft, minimum balance, daily limit, etc.) are respected here.
    if (!from->withdraw(amount)) {
        std::cout << "[ERROR] Transfer failed: could not withdraw from source account.\n";
        return false;
    }

    to->deposit(amount);
    std::cout << "[SUCCESS] Transferred $" << amount << " from " << from->getAccountNumber()
               << " to " << to->getAccountNumber() << ".\n";
    return true;
}
