#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Transaction {
private:
    double amount;
    string type;
    string timestamp;
    double balanceAfter;

public:
    Transaction(string type, double amount, double balanceAfter)
        : type(type), amount(amount), balanceAfter(balanceAfter) {
        this->timestamp = "2026-09-02"; 
    }

    void displayTransaction() const {
        cout << "[" << timestamp << "] " << type 
             << ": $" << fixed << setprecision(2) << amount 
             << " | Balance: $" << balanceAfter << endl;
    }
};

class BankAccount {
protected:
    string accountNumber;
    string accountHolder;
    double balance;
    vector<Transaction> transactions;
    bool isClosed;

public:
    BankAccount(string accNum, string accHolder, double initialBalance, bool isClosed = false)
        : accountNumber(accNum), accountHolder(accHolder), balance(initialBalance), isClosed(isClosed) {
        transactions.push_back(Transaction("Account Opened", initialBalance, initialBalance));
    }



   void Deposit(double ammount){
    if(ammount > 0 &&  !isClosed){

        this->balance +=ammount;
          transactions.push_back(Transaction("Deposit",ammount , balance));
    }else{
        cout << "Error: Invalid amount or Account is Closed!\n";
    }
   }
   virtual bool withdraw(double ammount)
   { 
        if(ammount <= balance && !isClosed){
            this->balance -=ammount;
            cout << "Successfull :)\n";
      transactions.push_back(Transaction("Withdrawal",ammount , balance));
             
            return true;
        }else{
            cout <<"Sory there isn't enaougth Balacne ):\n";
            return false;
        }
   }
// Getters:
string getAccountNumber() const { return accountNumber; }
double  GetBalance() const{
    return this->balance;
}

virtual string getAccountType()const { 
    return "Standard Account";
 }


virtual void GetAccountInfo() const {
       cout << "\n==================================================\n"
             << "                 ACCOUNT SUMMARY                  \n"
             << "==================================================\n";
    cout << setw(17) << "Account Number "  << getAccountNumber()  << "\n";
    cout << setw(17) << "Account Holder " << accountHolder << "\n";
    cout << setw(17) << "Account Type " << getAccountType() <<"\n";
    cout << setw(17) << "Account State " << (isClosed?" Closed " : " Open ") <<"\n";
    cout << "--------------------------------------------------\n";
    cout << setw(17) << "Account Balance  $ : " << GetBalance( ) << "\n";
    cout << "==================================================\n\n";
}
virtual bool closeAccount(){
    if(balance != 0){
        cout << "Erorr Your Balance must be 0.00 To close Please Withdraw all your Balance \n";
        return false;
    }else{
        isClosed = 1;
        cout << "[SUCCES] Your Account Hase Been Closed \n";
       return true;
    }
}
virtual void displayTransactionHistory(){
    cout <<"\n     =======Transaction History======   \n";
    cout << "     =======for account " << accountHolder << "=======\n";
    for(auto & tran :transactions ){
        tran.displayTransaction();
    }
}
virtual ~BankAccount() = default;
};

class SavingAccount : public BankAccount{
    private:
    double interestRate; 
    double minimumBalance;
    public:
    SavingAccount(string accNum, string accHolder, double initialBalance,bool isClosed,double intres, double minim):
     BankAccount(accNum,accHolder,initialBalance,isClosed),
    interestRate(intres) , minimumBalance(minim){
         
    }
bool withdraw(double ammount) override {
        if (isClosed) {
            cout << "Cannot withdraw: Account is Closed!\n";
            return false;
        }
        if (ammount <= 0) {
            cout << "Invalid withdrawal amount!\n";
            return false;
        }
        if (balance - ammount < minimumBalance) {
            cout << "Sorry, balance cannot go below minimum required: $" << minimumBalance << "\n"; 
            return false;
        } else {
            this->balance -= ammount;
            cout << "Withdrawal Successful :)\n";
            transactions.push_back(Transaction("Withdrawal", ammount, balance));
            return true;
        }
    }
  void ApplyInterest(){
    if(!isClosed)
    {  
         double addbalance = balance * interestRate;
      balance +=addbalance;
      transactions.push_back(Transaction("Apply Interest" , addbalance, balance));
      cout << "[SUCCESS] Interest applied: +$" << addbalance << "\n";
    }
      
  }
 string getAccountType()const override{
       return "Saving Account";
  }
   
};

class CheckingAccount : public  BankAccount{
    private:
      double overdraftLimit;
      double transactionFee ;
    public:
    CheckingAccount(string accNum, string accHolder, double initialBalance,bool isClosed,double overdraftlimit_,double transactionfee_):
    BankAccount(accNum,accHolder,initialBalance,isClosed),overdraftLimit(overdraftlimit_),transactionFee(transactionfee_) 
    {

     }
 void chargeTransactionFee(){
    balance -=transactionFee;
    transactions.push_back(Transaction("ChargeTransactionFee",transactionFee,balance));
 }
bool withdraw(double ammount) override {
     double totalDeduction = ammount + transactionFee;
        if (isClosed) {
            cout << "Cannot withdraw: Account is Closed!\n";
            return false;
        }
        if (ammount <= 0) {
            cout << "Invalid withdrawal amount!\n";
            return false;
        }
        if ((balance + overdraftLimit) >= totalDeduction    ) {
            this->balance -= ammount;
            cout << "Withdrawal Successful :)\n";
            transactions.push_back(Transaction("Withdrawal", ammount, balance));
            chargeTransactionFee();
            return true;
        } else {
            cout << "[ERROR] Transaction failed: Exceeds overdraft limit!\n"; 
            return false;
        }
    }


    // geters
     string getAccountType()const override{
        return "Checking Account";
     }
};
class BusinessAccount : public BankAccount{
private: 
double dailyWithdrawalLimit;
double overdarftLimit;
double totalWithdrawnToday;

public:
BusinessAccount(string accNum, string accHolder, double initialBalance,bool isClosed,double dailyWithdrawalLimit_,double overdarftLimit_,double totalWithdrawnToday_):
    BankAccount(accNum,accHolder,initialBalance,isClosed),dailyWithdrawalLimit(dailyWithdrawalLimit_),overdarftLimit(overdarftLimit_),totalWithdrawnToday(totalWithdrawnToday_) {

    }
    bool withdraw(double ammount) override{
        double totalde = balance + overdarftLimit;
        if (isClosed) {
            cout << "Cannot withdraw: Account is Closed!\n";
            return false;
        }
        if (ammount <= 0) {
            cout << "Invalid withdrawal amount!\n";
            return false;
        }
        if(balance + overdarftLimit < ammount)
{
    cout << "[ERROR] Cannot withdraw: Exceeds available balance + overdraft limit!\n";
    return false;
}  
 if(totalWithdrawnToday+ ammount > dailyWithdrawalLimit){
    cout << "[ERROR] Cannot withdraw  Exceed available balance + overdraft limit!\n";
  return false;     
} 
     
       balance-=ammount;
       totalWithdrawnToday+=ammount;
        transactions.push_back(Transaction("Business Withdrawal",ammount,balance));
        cout << "[SUCCESS] Withdrawal success\n";
        return true;
    }
 string getAccountType() const override{
    return "Business Account";
 }
};

class LoanAccount: public BankAccount{
    private:
    double originalLoanAmount; 
    double interestRate;     
    double monthlyInstallment; 
    public:
    LoanAccount(string accNum, string accHolder, double initialBalance,bool isClosed,double originalLoanAmountـ,double interestRate_,double totalWithdrawnToday_, double monthlyInstallment_):
    BankAccount(accNum,accHolder,initialBalance,isClosed),originalLoanAmount(originalLoanAmountـ),interestRate(interestRate_), monthlyInstallment(monthlyInstallment_){

    }

bool withdraw(double amount) override {
        cout << "[ERROR] Cannot withdraw funds from a Loan Account! You can only make payments.\n";
        return false;
    }
    bool payInstallment(double amount){
       if (isClosed) {
            cout << "[ERROR] Account is Closed!\n";
            return false;
        }
        if (amount <= 0) {
            cout << "[ERROR] Invalid payment amount!\n";
            return false;
        }
       if(amount > balance){
        cout << "[ERORR]  Payment exceeds remining dept! \n"; return false;
       }
       balance -=amount;
       transactions.push_back(Transaction("Loan Rapymanet", amount,balance));
       cout << "[SUCCESS] Payment of $" << amount << " received. Remaining Debt: $" << balance << "\n";
     if (balance == 0) {
            cout << "[CONGRATS] The loan has been fully paid off!\n";
        }
        return true;
    }
    void ApplyInterestRate(){
        double interestApplaying = interestRate* balance;
        balance +=interestApplaying;
        transactions.push_back(Transaction("Applyinh Interest",interestApplaying,balance));

    }
    string getAccountType() const override{
        return "Loan Account";
    }
};
class Bank{
private:
string bankName;
int nextAccountNumber;
vector<BankAccount*>BankAccounts;
string genAccountNumber(const string &prfx){
    return prfx + "-" + to_string(++nextAccountNumber);
}
public:
Bank(string name, int nextaccnn = 1000) : bankName(name) , nextAccountNumber(nextaccnn){

}

SavingAccount *CreataSavingAccount(string holde,double intiaitlBalance ,double interestRate,double minimumBalance){
    string Accnum = genAccountNumber("SAV");
  SavingAccount * sav = new SavingAccount(Accnum,holde,intiaitlBalance,false,interestRate,minimumBalance);
  BankAccounts.push_back(sav);
  cout << "[SUCCESS] Saving Account created for " << holde << " with ID: " << Accnum << "\n";
 return sav;

}

CheckingAccount *CreataCheckingAccount(string holde,double intiaitlBalance ,double overdraftlimit_,double transactionfee_){
    string Accnum = genAccountNumber("CHK");
  CheckingAccount * chek = new CheckingAccount(Accnum,holde,intiaitlBalance,false,overdraftlimit_,transactionfee_);
  BankAccounts.push_back(chek);
  cout << "[SUCCESS] Checking Account created for " << holde << " with ID: " << Accnum << "\n";
 return chek;

}

BusinessAccount* CreatBusinessAccount(string holde,double intiaitlBalance ,double dailyWithdrawalLimit_,double overdarftLimit_,double totalWithdrawnToday_){
    string Accnum = genAccountNumber("BUS");
  BusinessAccount* bus = new BusinessAccount(Accnum,holde,intiaitlBalance,false,dailyWithdrawalLimit_,overdarftLimit_,totalWithdrawnToday_);
  BankAccounts.push_back(bus);
  cout << "[SUCCESS] Business Account created for " << holde << " with ID: " << Accnum << "\n";
 return bus;

}
LoanAccount *CreataLoanAccount(string holde,double intiaitlBalance ,double originalLoanAmountـ,double interestRate_,double totalWithdrawnToday_, double monthlyInstallment_){
    string Accnum = genAccountNumber("LON");
    LoanAccount * lona = new LoanAccount(Accnum,holde,intiaitlBalance,false,originalLoanAmountـ,interestRate_,totalWithdrawnToday_,monthlyInstallment_);
  BankAccounts.push_back(lona);
  cout << "[SUCCESS] Loan Account created for " << holde << " with ID: " << Accnum << "\n";
 return lona;

}
BankAccount* FindAccount(string AccNum){
    for(auto * acc: BankAccounts){
        if(acc->getAccountNumber() == AccNum){
            cout << "[SUCCESS] The Account is on the system \n";
            return acc;
        }
    }
    cout <<"[ERORR] The Account is not Define\n";
    return nullptr;
}

double GetTotalBankBalance() const{
    double total  = 0;
    for(BankAccount * account: BankAccounts){
        total+=account->GetBalance();
    }
    return total;
}
void displayAllAccounts() const {

    if (BankAccounts.empty()) {
        cout << "[INFO] No accounts currently registered in the bank system.\n";
        return;
    }


    cout << "\n==================================================\n";
    cout << "        TOTAL REGISTERED ACCOUNTS: " << BankAccounts.size() << "\n";
    cout << "==================================================\n";


    for ( const auto* acc : BankAccounts) {
        if (acc != nullptr) {
            acc->GetAccountInfo();
        }
    }
}
bool executeTransfer(BankAccount *from, BankAccount *to, double amount) {
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

    to->Deposit(amount);
    std::cout << "[SUCCESS] Transferred $" << amount << " from " << from->getAccountNumber()
               << " to " << to->getAccountNumber() << ".\n";
    return true;
}

};
int main(){
    Bank myBank("Egypt National Bank");

    SavingAccount *mahmoud = myBank.CreataSavingAccount("Mahmoud", 1000000, 0.2, 100);
    CheckingAccount *sara = myBank.CreataCheckingAccount("Sara", 5000, 2000, 25);

    mahmoud->Deposit(500);
    mahmoud->ApplyInterest();

    myBank.executeTransfer(mahmoud, sara, 1500);

    myBank.displayAllAccounts();
    mahmoud->displayTransactionHistory();

    std::cout << "Total bank balance: $" << myBank.GetTotalBankBalance() << "\n";
  
    
    return 0;
}