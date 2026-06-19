#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// represents deposit or withdrawel
class Transaction
{
private:
    double amount;
    string type;
    string date;

public:
    Transaction(double a, string t, string d) : amount(a), type(t), date(d) {}

    void getInfo()
    {
        cout << type << ": " << amount << " on " << date << endl;
    };
    double getAmount()
    {
        return amount;
    };
    string getType()
    {
        return type;
    };
    string getDate()
    {
        return date;
    };
};

// holds customers's account state
class Account
{
private:
    int accountNumber;
    string owner;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int aN, string o, double b) : accountNumber(aN), owner(o), balance(b) {}

    int deposit(double amount)
    {
        cout << "Your account transaction is: " << balance << " + " << amount << endl;
        balance += amount;
        transactions.push_back(Transaction(amount, "Deposit", "today"));
        return 0;
    };
    int withdraw(double amount)
    {
        if (amount <= balance)
        {
            cout << "Your account transaction is: " << balance << " - " << amount << endl;
            balance -= amount;
            transactions.push_back(Transaction(amount, "Withdraw", "today"));
            return 0;
        }
        else
        {
            cout << "Insufficient funds" << endl;
            return -1;
        }
    };
    void showAccount()
    {
        cout << owner << "'s account number is " << accountNumber << " and you have " << balance << "€" << endl;
    };
    void showTransactions()
    {
        for (size_t i = 0; i < transactions.size(); i++)
        {
            transactions[i].getInfo();
        }
    };
    double getBalance()
    {
        return balance;
    }
    int getAccountNumber()
    {
        return accountNumber;
    }
    string getOwner()
    {
        return owner;
    }
};

// the bank which holds and manages all accounts
class Bank
{
private:
    vector<Account> accounts;
    string bankName;
    int nextAccountNumber = 1000;

public:
    int createAccount()
    {
        string owner;
        double initDeposit;

        cout << "Enter owner name: ";
        if (!(cin >> owner))
        {
            cout << "Invalid owner name." << endl;
            clearInputBuffer();
            return -1;
        }
        cout << "Enter initial deposit: ";
        if (!(cin >> initDeposit))
        {
            cout << "Invalid amount." << endl;
            clearInputBuffer();
            return -1;
        }
        clearInputBuffer();

        // creates new account and adds to list
        Account newAccount(nextAccountNumber, owner, initDeposit);
        accounts.push_back(newAccount);

        cout << "Account for " << owner << " created with account number: " << nextAccountNumber << endl;
        nextAccountNumber++;
        return 0;
    };
    int findAccount(int accountNumber)
    {
        for (size_t i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].getAccountNumber() == accountNumber)
            {
                return i;
            }
        }
        cout << "Account not found." << endl;
        return -1;
    };
    int showAllAccounts()
    {
        for (size_t i = 0; i < accounts.size(); i++)
        {
            accounts[i].showAccount();
        }
        return 0;
    };
    vector<Account> &getAccounts()
    {
        return accounts;
    }
};

int main()
{
    Bank bank;
    int input;
    bool running = true;

    while (running)
    {
        cout << "1: create account" << endl;
        cout << "2: deposit" << endl;
        cout << "3: withdraw" << endl;
        cout << "4: show account" << endl;
        cout << "5: show all accounts" << endl;
        cout << "6: exit" << endl;

        if (!(cin >> input))
        {
            cout << "Invalid option" << endl;
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (input)
        {
        case 1: // create account
            bank.createAccount();
            break;
        case 2:
        { // deposit
            int accNum;
            double amount;
            cout << "Account number: ";
            if (!(cin >> accNum))
            {
                cout << "Invalid account number." << endl;
                clearInputBuffer();
                break;
            }
            cout << "Amount: ";
            if (!(cin >> amount))
            {
                cout << "Invalid amount." << endl;
                clearInputBuffer();
                break;
            }
            clearInputBuffer();
            int idx = bank.findAccount(accNum);
            if (idx != -1)
            {
                bank.getAccounts()[idx].deposit(amount);
                bank.getAccounts()[idx].showAccount();
            }
            break;
        }
        case 3:
        { // withdraw
            int accNum;
            double amount;
            cout << "Account number: ";
            if (!(cin >> accNum))
            {
                cout << "Invalid account number." << endl;
                clearInputBuffer();
                break;
            }
            cout << "Amount: ";
            if (!(cin >> amount))
            {
                cout << "Invalid amount." << endl;
                clearInputBuffer();
                break;
            }
            clearInputBuffer();
            int idx = bank.findAccount(accNum);
            if (idx != -1)
            {
                bank.getAccounts()[idx].withdraw(amount);
                bank.getAccounts()[idx].showAccount();
            }
            break;
        }
        case 4:
        { // show account
            int accNum;
            cout << "Account number: ";
            if (!(cin >> accNum))
            {
                cout << "Invalid account number." << endl;
                clearInputBuffer();
                break;
            }
            clearInputBuffer();
            int idx = bank.findAccount(accNum);
            if (idx != -1)
            {
                bank.getAccounts()[idx].showAccount();
            }
            break;
        }
        case 5:
        { // show all accounts
            bank.showAllAccounts();
            break;
        }
        case 6:
        { // exit
            running = false;
            break;
        }
        default:
        {
            cout << "Invalid option" << endl;
            break;
        }
        }
    }
    return 0;
}