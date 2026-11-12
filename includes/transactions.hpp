#pragma once

#include <string>

class Transaction
{
public:
    Transaction(double amount, std::string type, std::string date);

    void getInfo() const;
    double getAmount() const;
    std::string getType() const;
    std::string getDate() const;

private:
    double amount;
    std::string type;
    std::string date;
};
