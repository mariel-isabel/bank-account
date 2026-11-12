#pragma once

#include "stuff.hpp"
#include "transactions.hpp"

#include <string>
#include <vector>

class Account
{
public:
    Account(int accountNumber, std::string owner, double balance);
    virtual ~Account() = default;

    int deposit(double amount);
    virtual int withdraw(double amount);
    void showAccount() const;
    void showTransactions() const;
    void showTransactionsByType(const std::string& type) const;
    double getBalance() const;
    int getAccountNumber() const;
    std::string getOwner() const;

protected:
    void addTransaction(double amount, const std::string& type);
    double balance;

private:
    int accountNumber;
    std::string owner;
    std::vector<Transaction> transactions;
};

class SavingsAccount : public Account
{
public:
    SavingsAccount(int accountNumber, std::string owner, double balance);
    int regularDeposit(double amount);

private:
    double interestRate;
};

class CheckingAccount : public Account
{
public:
    CheckingAccount(int accountNumber, std::string owner, double balance,
                    double overdraftLimit = DEFAULT_OVERDRAFT_LIMIT);
    int withdraw(double amount) override;
    void showWithdraws() const;

private:
    double overdraftLimit;
};
