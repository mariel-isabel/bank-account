#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Account{
private:
    int accountNumber;
    string owner;
    double balance;
    vector<Transaction> transactions;

public:
    int deposit();
    int withdraw();
    int showAccount();
    int showTransactions();
};


class Transaction{
private:
    double amount;
    string type;
    string date;

public:
    void getInfo();
    double getAmount();
};


class Bank{
private:
    vector<Account> accounts;
    string bankName;

public:
    int createAccount();
    int findAccount();
    int showAllAccounts();
};