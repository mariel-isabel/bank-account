#include "includes/bank.hpp"
#include "includes/stuff.hpp"

#include <iostream>
#include <string>

int main()
{
    Bank bank("Bank");
    bank.loadFromFile("accounts.txt");
    int input;
    bool running = true;

    while (running)
    {
        std::cout << "1: create account" << std::endl;
        std::cout << "2: deposit" << std::endl;
        std::cout << "3: withdraw" << std::endl;
        std::cout << "4: show account" << std::endl;
        std::cout << "5: show transaction history" << std::endl;
        std::cout << "6: show all accounts" << std::endl;
        std::cout << "7: find [name] account" << std::endl;
        std::cout << "8: exit" << std::endl;

        if (!(std::cin >> input))
        {
            std::cout << "Invalid option" << std::endl;
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (input)
        {
        case 1:
            bank.createAccount();
            break;
        case 2:
        {
            int accountNumber;
            double amount;
            std::cout << "Account number: ";
            if (!(std::cin >> accountNumber))
            {
                std::cout << "Invalid account number." << std::endl;
                clearInputBuffer();
                break;
            }
            std::cout << "Amount: ";
            if (!(std::cin >> amount))
            {
                std::cout << "Invalid amount." << std::endl;
                clearInputBuffer();
                break;
            }
            clearInputBuffer();
            const int index = bank.findAccount(accountNumber);
            if (index != -1)
            {
                bank.getAccount(static_cast<std::size_t>(index)).deposit(amount);
                bank.getAccount(static_cast<std::size_t>(index)).showAccount();
            }
            break;
        }
        case 3:
        {
            int accountNumber;
            double amount;
            std::cout << "Account number: ";
            if (!(std::cin >> accountNumber))
            {
                std::cout << "Invalid account number." << std::endl;
                clearInputBuffer();
                break;
            }
            std::cout << "Amount: ";
            if (!(std::cin >> amount))
            {
                std::cout << "Invalid amount." << std::endl;
                clearInputBuffer();
                break;
            }
            clearInputBuffer();
            const int index = bank.findAccount(accountNumber);
            if (index != -1)
            {
                bank.getAccount(static_cast<std::size_t>(index)).withdraw(amount);
                bank.getAccount(static_cast<std::size_t>(index)).showAccount();
            }
            break;
        }
        case 4:
        {
            int accountNumber;
            std::cout << "Account number: ";
            if (!(std::cin >> accountNumber))
            {
                std::cout << "Invalid account number." << std::endl;
                clearInputBuffer();
                break;
            }
            clearInputBuffer();
            const int index = bank.findAccount(accountNumber);
            if (index != -1)
            {
                bank.getAccount(static_cast<std::size_t>(index)).showAccount();
            }
            break;
        }
        case 5:
        {
            int accountNumber;
            std::cout << "Account number: ";
            if (!(std::cin >> accountNumber))
            {
                std::cout << "Invalid account number." << std::endl;
                clearInputBuffer();
                break;
            }
            clearInputBuffer();
            const int index = bank.findAccount(accountNumber);
            if (index != -1)
            {
                bank.getAccount(static_cast<std::size_t>(index)).showTransactions();
            }
            break;
        }
        case 6:
            bank.showAllAccounts();
            break;
        case 7:
        {
            std::string accountName;
            std::cout << "Find account by name: " << std::endl;
            if (!(std::cin >> accountName))
            {
                std::cout << "Invalid owner name." << std::endl;
                clearInputBuffer();
                break;
            }
            clearInputBuffer();
            const int index = bank.findAccountByName(accountName);
            if (index != -1)
            {
                bank.getAccount(static_cast<std::size_t>(index)).showAccount();
            }
            break;
        }
        case 8:
            bank.saveToFile("accounts.txt");
            running = false;
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            break;
        }
    }
    return 0;
}
