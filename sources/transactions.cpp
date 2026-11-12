#include "transactions.hpp"

#include <iostream>
#include <utility>

Transaction::Transaction(double amount, std::string type, std::string date)
    : amount(amount), type(std::move(type)), date(std::move(date))
{
}

void Transaction::getInfo() const
{
    std::cout << type << ": " << amount << " on " << date << std::endl;
}

double Transaction::getAmount() const
{
    return amount;
}

std::string Transaction::getType() const
{
    return type;
}

std::string Transaction::getDate() const
{
    return date;
}