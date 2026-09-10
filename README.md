# 🏦 Bank Management System

A C++ console application that simulates a bank's core account operations, built with clean object-oriented design: multiple account types, polymorphic transaction rules, transaction history, and inter-account transfers.

## ✨ Highlights

- ✅ — Completed feature
- 🔧 — Implementation detail
- ⚠️ — Important note

## 🧩 Features

### 💳 Account Types
- ✅ **Saving Account** — earns interest, enforces a minimum balance
- ✅ **Checking Account** — overdraft limit, per-withdrawal transaction fee
- ✅ **Business Account** — overdraft limit + daily withdrawal cap
- ✅ **Loan Account** — deposit-only via installment payments; withdrawals are blocked by design

### 🏦 Core Banking Operations
- ✅ Open new accounts (Saving / Checking / Business / Loan)
- ✅ Deposit and withdraw funds, with each account type enforcing its own rules via polymorphism
- ✅ Transfer money between any two accounts (`Bank::executeTransfer`)
- ✅ Full transaction history per account, with real timestamps
- ✅ Look up an account by account number
- ✅ View total balance across the whole bank
- ✅ List/print a summary of every registered account

### 🔒 Memory & Code Quality
- ✅ Accounts are owned by `Bank` via `std::unique_ptr` — no manual `delete`, no leaks
- ✅ Compiles cleanly with `-Wall -Wextra`, zero warnings
- ✅ Virtual destructors and `override` used throughout the class hierarchy

## 🏛️ Architecture

```
BankAccount (abstract base)
 ├── SavingAccount
 ├── CheckingAccount
 ├── BusinessAccount
 └── LoanAccount

Transaction   — an immutable record of a single account event
Bank          — owns and manages all accounts, handles transfers & lookups
```

- **Inheritance & polymorphism**: every account type overrides `withdraw()` and `getAccountType()` with its own rules; `Bank::executeTransfer` calls `withdraw()` polymorphically, so it automatically respects overdraft limits, minimum balances, and daily caps without knowing which account type it's dealing with.
- **RAII / smart pointers**: `Bank` stores accounts as `std::vector<std::unique_ptr<BankAccount>>`, so accounts are automatically destroyed with the bank.
- **Separation of concerns**: headers in `include/`, implementations in `src/`.

## 🗂️ Project Structure

```
bank-management-system/
├── include/                 # Class declarations
│   ├── Transaction.h
│   ├── BankAccount.h
│   ├── SavingAccount.h
│   ├── CheckingAccount.h
│   ├── BusinessAccount.h
│   ├── LoanAccount.h
│   └── Bank.h
├── src/                     # Class implementations
│   ├── Transaction.cpp
│   ├── BankAccount.cpp
│   ├── SavingAccount.cpp
│   ├── CheckingAccount.cpp
│   ├── BusinessAccount.cpp
│   ├── LoanAccount.cpp
│   ├── Bank.cpp
│   └── main.cpp
├── Makefile
├── .gitignore
├── LICENSE
└── README.md
```

## 🛠️ Requirements

- A C++17-compatible compiler (GCC, Clang, or MSVC)
- `make` (optional, but recommended)

## ▶️ Building and Running

### Using `make` (recommended)
```bash
make run
```
This builds the project into `bin/bank_system` and runs it. To just build without running:
```bash
make
```
To clean build artifacts:
```bash
make clean
```

> ⚠️ On some systems the default `g++` may not support C++17 or may be aliased incorrectly. If `make` fails, point it at your compiler explicitly, e.g.:
> ```bash
> make CXX=g++-16
> ```

### Manual compilation
```bash
g++ -std=c++17 -Wall -Wextra -Iinclude -o bank_system src/*.cpp
./bank_system
```

## 🧭 Usage

`src/main.cpp` contains a small demo: it creates a saving account and a checking account, makes a deposit, applies interest, executes a transfer between the two accounts, then prints an account summary and transaction history.

```cpp
Bank myBank("Egypt National Bank");
SavingAccount *mahmoud = myBank.createSavingAccount("Mahmoud", 1000000, 0.2, 100);
CheckingAccount *sara  = myBank.createCheckingAccount("Sara", 5000, 2000, 25);

mahmoud->deposit(500);
mahmoud->applyInterest();
myBank.executeTransfer(mahmoud, sara, 1500);

myBank.displayAllAccounts();
```

Feel free to edit `main.cpp` to try your own scenarios — open a `LoanAccount`, make a `BusinessAccount` hit its daily withdrawal limit, etc.

## 🔧 Notable Design Decisions

- `LoanAccount::withdraw()` is overridden to always fail — a loan account can only be paid down via `payInstallment()`, never withdrawn from.
- `CheckingAccount::withdraw()` deducts the withdrawal amount **and** a flat transaction fee in the same call, and only succeeds if `balance + overdraftLimit` covers both.
- Every transaction is timestamped with the real system date (`<ctime>`), not a hardcoded value.

## 📜 License

This project is licensed under the MIT License — see [LICENSE](LICENSE) for details.
