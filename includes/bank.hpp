#pragma once

#include "accounts.hpp"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

class Bank
{
public:
    explicit Bank(std::string name);

    int createAccount();
    int findAccount(int accountNumber) const;
    int findAccountByName(const std::string& accountName) const;
    int showAllAccounts() const;
    int transfer(int fromNumber, int toNumber, double amount);
    Account& getAccount(std::size_t index);
    const Account& getAccount(std::size_t index) const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

private:
    std::vector<std::unique_ptr<Account>> accounts;
    std::string bankName;
    int nextAccountNumber;
};
