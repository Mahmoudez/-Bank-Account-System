#include "Transaction.h"
#include <iomanip>
#include <iostream>
#include <ctime>
#include <sstream>

// Helper: gets the current date as "YYYY-MM-DD" instead of a hardcoded string
static std::string getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm tmBuf{};
#if defined(_WIN32)
    localtime_s(&tmBuf, &t);
#else
    localtime_r(&t, &tmBuf);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tmBuf, "%Y-%m-%d");
    return oss.str();
}

Transaction::Transaction(std::string type, double amount, double balanceAfter)
    : amount(amount), type(std::move(type)), balanceAfter(balanceAfter) {
    this->timestamp = getCurrentDate();
}

void Transaction::displayTransaction() const {
    std::cout << "[" << timestamp << "] " << type 
    << ": $" << std::fixed << std::setprecision(2) << amount
     << " | Balance: $" << balanceAfter << std::endl;
}
