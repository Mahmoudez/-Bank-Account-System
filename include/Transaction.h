#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    double amount;
    std::string type;
    std::string timestamp;
    double balanceAfter;

public:
    Transaction(std::string type, double amount, double balanceAfter);

    void displayTransaction() const;
};

#endif // TRANSACTION_H
