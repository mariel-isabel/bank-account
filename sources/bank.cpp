#include "bank.hpp"

#include "stuff.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

Bank::Bank(std::string name)
    : bankName(std::move(name)), nextAccountNumber(START_ACC_NUM)
{
}

int Bank::createAccount()
{
    std::string owner;
    double initialDeposit;

    std::cout << "Enter owner name: ";
    if (!(std::cin >> owner))
    {
        std::cout << "Invalid owner name." << std::endl;
        clearInputBuffer();
        return -1;
    }
    std::cout << "Enter initial deposit: ";
    if (!(std::cin >> initialDeposit))
    {
        std::cout << "Invalid amount." << std::endl;
        clearInputBuffer();
        return -1;
    }
    clearInputBuffer();

    accounts.push_back(std::make_unique<Account>(nextAccountNumber, owner, initialDeposit));
    std::cout << "Account for " << owner << " created with account number: "
              << nextAccountNumber << std::endl;
    ++nextAccountNumber;
    return 0;
}

int Bank::findAccount(int accountNumber) const
{
    for (std::size_t index = 0; index < accounts.size(); ++index)
    {
        if (accounts[index]->getAccountNumber() == accountNumber)
        {
            return static_cast<int>(index);
        }
    }
    std::cout << "Account not found." << std::endl;
    return -1;
}

int Bank::findAccountByName(const std::string& accountName) const
{
    for (std::size_t index = 0; index < accounts.size(); ++index)
    {
        if (accounts[index]->getOwner() == accountName)
        {
            return static_cast<int>(index);
        }
    }
    std::cout << "Account with name " << accountName << " was not found." << std::endl;
    return -1;
}

int Bank::showAllAccounts() const
{
    for (const std::unique_ptr<Account>& account : accounts)
    {
        account->showAccount();
    }
    return 0;
}

int Bank::transfer(int fromNumber, int toNumber, double amount)
{
    const int fromIndex = findAccount(fromNumber);
    const int toIndex = findAccount(toNumber);
    if (fromIndex == -1 || toIndex == -1)
    {
        return -1;
    }

    Account& fromAccount = *accounts[static_cast<std::size_t>(fromIndex)];
    Account& toAccount = *accounts[static_cast<std::size_t>(toIndex)];
    if (fromAccount.withdraw(amount) != 0)
    {
        return -1;
    }
    if (toAccount.deposit(amount) != 0)
    {
        fromAccount.deposit(amount);
        return -1;
    }

    std::cout << "Transfer successful.\n";
    return 0;
}

Account& Bank::getAccount(std::size_t index)
{
    return *accounts.at(index);
}

const Account& Bank::getAccount(std::size_t index) const
{
    return *accounts.at(index);
}

void Bank::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file)
    {
        std::cout << "Error saving file.\n";
        return;
    }

    for (const std::unique_ptr<Account>& account : accounts)
    {
        file << account->getAccountNumber() << ','
             << account->getOwner() << ','
             << account->getBalance() << '\n';
    }
    if (!file)
    {
        std::cout << "Error writing accounts file.\n";
        return;
    }
    std::cout << "Accounts saved.\n";
}

void Bank::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        return;
    }

    std::string line;
    std::size_t lineNumber = 0;
    while (std::getline(file, line))
    {
        ++lineNumber;
        if (line.empty())
        {
            continue;
        }

        std::istringstream record(line);
        std::string numberText;
        std::string owner;
        std::string balanceText;
        std::string extraField;
        if (!std::getline(record, numberText, ',') ||
            !std::getline(record, owner, ',') ||
            !std::getline(record, balanceText, ',') ||
            std::getline(record, extraField, ','))
        {
            std::cout << "Skipping invalid account record on line " << lineNumber << ".\n";
            continue;
        }

        std::istringstream numberStream(numberText);
        std::istringstream balanceStream(balanceText);
        int accountNumber;
        double balance;
        if (!(numberStream >> accountNumber) || (numberStream >> extraField) ||
            !(balanceStream >> balance) || (balanceStream >> extraField) ||
            accountNumber < 0)
        {
            std::cout << "Skipping invalid account record on line " << lineNumber << ".\n";
            continue;
        }

        accounts.push_back(std::make_unique<Account>(accountNumber, owner, balance));
        if (accountNumber >= nextAccountNumber)
        {
            nextAccountNumber = accountNumber + 1;
        }
    }
    if (file.bad())
    {
        std::cout << "Error reading accounts file.\n";
        return;
    }
    std::cout << "Accounts loaded.\n";
}
