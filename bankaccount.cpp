#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <ctime>
using namespace std;

void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getCurrentDate(){
    time_t now = time(0); 
    string dt = ctime(&now); 
    dt.pop_back(); 
    return dt; 
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

    void getInfo() const 
    {
        cout << type << ": " << amount << " on " << date << endl;
    };
    double getAmount() const 
    {
        return amount;
    };
    string getType() const
    {
        return type;
    };
    string getDate() const 
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
        if (amount <= 0){
            cout << "Invalid amount." << endl; 
            return -1; 
        }
        cout << "Your account transaction is: " << balance << " + " << amount << endl;
        balance += amount;
        transactions.push_back(Transaction(amount, "Deposit", getCurrentDate()));
        return 0;
    };
    int withdraw(double amount)
    {
        if (amount <= balance)
        {
            cout << "Your account transaction is: " << balance << " - " << amount << endl;
            balance -= amount;
            transactions.push_back(Transaction(amount, "Withdraw", getCurrentDate()));
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


// savings account, inherits from account
class SavingsAccount : public Account{
public: 
    SavingsAccount(int aN, string o, double b) : Account(aN, o, b){}
};


// the bank which holds and manages all accounts
class Bank
{
private:
    vector<Account> accounts;
    string bankName;
    int nextAccountNumber = 1000;

public:
    Bank(string name) : bankName(name){}

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
    int transfer(int fromNum, int toNum, double amount){
        int fromIdx = findAccount(fromNum); 
        int toIdx = findAccount(toNum); 
        if(fromIdx == -1 || toIdx == -1){ return -1; }
        int result = getAccounts()[fromIdx].withdraw(amount); 
        if(result == 0){
            getAccounts()[toIdx].deposit(amount); 
            cout << "Transfer successful.\n"; 
        }
        return result; 
    }
    vector<Account> &getAccounts()
    {
        return accounts;
    }
};

int main()
{
    Bank bank("Bank"); 
    int input;
    bool running = true;

    while (running)
    {
        cout << "1: create account" << endl;
        cout << "2: deposit" << endl;
        cout << "3: withdraw" << endl;
        cout << "4: show account" << endl;
        cout << "5: show transaction history" << endl; 
        cout << "6: show all accounts" << endl;
        cout << "7: exit" << endl;

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
        case 5: {
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
                bank.getAccounts()[idx].showTransactions();
            }
            break;
        }
        case 6:
        { // show all accounts
            bank.showAllAccounts();
            break;
        }
        case 7:
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