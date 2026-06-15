#include <iostream>
#include <vector>
#include <string>
using namespace std;

// represents deposit or withdrawel 
class Transaction{
private:
    double amount;
    string type;
    string date;

public:
    Transaction (double a, string t, string d) : amount(a), type(t), date(d){}

    void getInfo(){
        cout << type << ": " << amount << " on " << date << endl;
    };
    double getAmount(){
        return amount; 
    };
    string getType(){
        return type; 
    }; 
    string getDate(){
        return date; 
    }; 
};


// holds customers's account state 
class Account{
private:
    int accountNumber;
    string owner;
    double balance;
    vector<Transaction> transactions;

public:
    Account (int aN, string o, double b) : accountNumber(aN), owner(o), balance(b){}

    int deposit(double amount){
        balance += amount; 
        transactions.push_back(Transaction(amount, "Deposit", "today"));
        return 0; 
    };
    int withdraw(double amount){
        if (amount <= balance){
            balance -= amount; 
            transactions.push_back(Transaction(amount, "Withdraw", "today")); 
            return 0; 
        } else { 
            cout << "Insufficient funds" << endl; 
            return -1; 
        }
    };
    void showAccount(){
        cout << owner << "'s account number is " << accountNumber << " and you have " << balance << endl; 
    };
    void showTransactions(){
        for (size_t i = 0; i < transactions.size(); i++){
            transactions[i].getInfo(); 
        }
    };
    double getBalance(){
        return balance; 
    }
    int getAccountNumber(){
        return accountNumber; 
    }
    string getOwner(){
        return owner; 
    }
};


// the bank which holds and manages all accounts
class Bank{
private:
    vector<Account> accounts;
    string bankName;
    int nextAccountNumber = 1000; 

public:
    int createAccount(){
        string owner; 
        double initDeposit; 

        cout << "Enter owner name: "; 
        cin >> owner; 
        cout << "Enter initial deposit: "; 
        cin >> initDeposit; 
        
        Account newAccount(nextAccountNumber, owner, initDeposit); 
        accounts.push_back(newAccount); 
        
        cout << "Account created with number " << nextAccountNumber << endl; 
        nextAccountNumber++; 
        return 0;  
    };
    int findAccount(int accountNumber){
        for (size_t i = 0; i < accounts.size(); i++){
            if (accounts[i].getAccountNumber() == accountNumber){
                return i; 
            } 
        }
        cout << "Account not found." << endl; 
        return -1; 
    };
    int showAllAccounts(){
        for (size_t i = 0; i < accounts.size(); i++){
            accounts[i].showAccount(); 
        }
        return 0; 
    };
    vector<Account>& getAccounts(){
        return accounts; 
    }
};


int main(){
    Bank bank; 
    int input; 
    bool running = true; 
 
    while(running){
        cout << "1: create account" << endl; 
        cout << "2: deposit" << endl; 
        cout << "3: withdraw" << endl; 
        cout << "4: show account" << endl; 
        cout << "5: show all accounts" << endl; 
        cout << "6: exit" << endl; 

        cin >> input; 

        switch(input){
            case 1: 
                bank.createAccount(); 
                break; 
            case 2: {
                int accNum; 
                double amount; 
                cout << "Account number: "; 
                cin >> accNum; 
                cout << "Amount: "; 
                cin >> amount; 
                int idx = bank.findAccount(accNum); 
                if (idx != -1){
                    bank.getAccounts()[idx].deposit(amount); 
                }
                break; 
            }
            case 3: {
                int accNum; 
                double amount; 
                cout << "Account number: "; 
                cin >> accNum; 
                cout << "Amount: "; 
                cin >> amount; 
                int idx = bank.findAccount(accNum); 
                if (idx != -1){
                    bank.getAccounts()[idx].withdraw(amount); 
                }
                break; 
            }
            case 4: {
                int accNum; 
                cout << "Account number: "; 
                cin >> accNum; 
                int idx = bank.findAccount(accNum); 
                if (idx != -1){
                    bank.getAccounts()[idx].showAccount(); 
                }
                break; 
            }
            case 5: {
                bank.showAllAccounts(); 
                break; 
            }
            case 6: {
                running = false; 
                break; 
            }
            default: {
                cout << "Invalid option" << endl; 
            }
        }
    }
    return 0; 
}