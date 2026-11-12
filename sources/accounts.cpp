#include "accounts.hpp"

#include "stuff.hpp"

#include <iostream>
#include <utility>

Account::Account(int accountNumber, std::string owner, double balance)
    : balance(balance), accountNumber(accountNumber), owner(std::move(owner))
{
}

int Account::deposit(double amount)
{
    if (amount <= 0)
    {
        std::cout << "Invalid amount." << std::endl;
        return -1;
    }

    std::cout << "Your account transaction is: " << balance << " + " << amount << std::endl;
    balance += amount;
    addTransaction(amount, "Deposit");
    return 0;
}

int Account::withdraw(double amount)
{
    if (amount <= 0)
    {
        std::cout << "Invalid amount." << std::endl;
        return -1;
    }
    if (amount > balance)
    {
        std::cout << "Insufficient funds" << std::endl;
        return -1;
    }

    std::cout << "Your account transaction is: " << balance << " - " << amount << std::endl;
    balance -= amount;
    addTransaction(amount, "Withdraw");
    return 0;
}

void Account::showAccount() const
{
    std::cout << owner << "'s account number is " << accountNumber << " and you have "
              << balance << "€" << std::endl;
}

void Account::showTransactions() const
{
    for (const Transaction& transaction : transactions)
    {
        transaction.getInfo();
    }
}

void Account::showTransactionsByType(const std::string& type) const
{
    for (const Transaction& transaction : transactions)
    {
        if (transaction.getType() == type)
        {
            transaction.getInfo();
        }
    }
}

double Account::getBalance() const
{
    return balance;
}

int Account::getAccountNumber() const
{
    return accountNumber;
}

std::string Account::getOwner() const
{
    return owner;
}

void Account::addTransaction(double amount, const std::string& type)
{
    transactions.emplace_back(amount, type, getCurrentDate());
}

SavingsAccount::SavingsAccount(int accountNumber, std::string owner, double balance)
    : Account(accountNumber, std::move(owner), balance),
      interestRate(DEFAULT_INTEREST_RATE)
{
}

int SavingsAccount::regularDeposit(double amount)
{
    if (amount <= 0)
    {
        std::cout << "Invalid amount" << std::endl;
        return -1;
    }
    if (deposit(amount) != 0)
    {
        return -1;
    }

    const double interest = getBalance() * interestRate;
    deposit(interest);
    std::cout << "Interest applied: " << interest << " EUR\n";
    return 0;
}

CheckingAccount::CheckingAccount(int accountNumber, std::string owner, double balance,
                                 double overdraftLimit)
    : Account(accountNumber, std::move(owner), balance), overdraftLimit(overdraftLimit)
{
}

int CheckingAccount::withdraw(double amount)
{
    if (amount <= 0)
    {
        std::cout << "Invalid amount." << std::endl;
        return -1;
    }
    if (amount > balance + overdraftLimit)
    {
        std::cout << "Exceeds overdraft limit.\n";
        return -1;
    }

    std::cout << "Withdrawing " << amount << " (overdraft may apply)\n";
    balance -= amount;
    addTransaction(amount, "Withdraw");
    return 0;
}

void CheckingAccount::showWithdraws() const
{
    showTransactionsByType("Withdraw");
}
