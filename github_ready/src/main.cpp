#include "Bank.h"
#include <iostream>

int main() {
    Bank myBank("Egypt National Bank");

    SavingAccount *mahmoud = myBank.createSavingAccount("Mahmoud", 1000000, 0.2, 100);
    CheckingAccount *maryam = myBank.createCheckingAccount("maryam", 5000, 2000, 25);

    mahmoud->deposit(500);
    mahmoud->applyInterest();

    myBank.executeTransfer(mahmoud, maryam, 1500);

    myBank.displayAllAccounts();
    mahmoud->displayTransactionHistory();

    std::cout << "Total bank balance: $" << myBank.getTotalBankBalance() << "\n";

    return 0;
}
