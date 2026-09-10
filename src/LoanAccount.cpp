#include "LoanAccount.h"
#include <iostream>

LoanAccount::LoanAccount(std::string accNum, std::string accHolder, double initialBalance,
    bool isClosed, double originalLoanAmount, double interestRate,
    double monthlyInstallment)
: BankAccount(std::move(accNum), std::move(accHolder), initialBalance, isClosed),
originalLoanAmount(originalLoanAmount), interestRate(interestRate),
monthlyInstallment(monthlyInstallment) {
}

bool LoanAccount::withdraw(double /*amount*/) {
    std::cout << "[ERROR] Cannot withdraw funds from a Loan Account! You can only make payments.\n";
    return false;
}

bool LoanAccount::payInstallment(double amount) {
    if (isClosed) {
        std::cout << "[ERROR] Account is Closed!\n";
        return false;
    }
    if (amount <= 0) {
        std::cout << "[ERROR] Invalid payment amount!\n";
        return false;
    }
    if (amount > balance) {
        std::cout << "[ERROR] Payment exceeds remaining debt!\n";
        return false;
    }
    balance -= amount;
    transactions.push_back(Transaction("Loan Repayment", amount, balance));
    std::cout << "[SUCCESS] Payment of $" << amount << " received. Remaining Debt: $" << balance << "\n";
    if (balance == 0) {
        std::cout << "[CONGRATS] The loan has been fully paid off!\n";
    }
    return true;
}

void LoanAccount::applyInterestRate() {
    double appliedInterest = interestRate * balance;
    balance += appliedInterest;
    transactions.push_back(Transaction("Applying Interest", appliedInterest, balance));
}

std::string LoanAccount::getAccountType() const {
    return "Loan Account";
}
