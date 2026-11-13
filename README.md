# bank-account

### What is it? 
The C++ banking application is a terminal-based system that manages bank accounts, processes financial transactions, and persists data to a text file. It utilizes object-oriented principles, including inheritance and polymorphism, to support different account types.

### What can it do?
- **Account Management**: Users can create new accounts, search for accounts by ID or owner name, and view all system accounts.
- **Transactions**: Supports depositing funds, withdrawing funds, and transferring money between accounts.
- **History Tracking**: Automatically logs every transaction with a timestamp and allows users to view an account's full transaction history or filter by transaction type.
- **Persistence**: Loads existing accounts from `accounts.txt` on startup and saves the updated state back to the file upon exit.

### Structure: 
This project is split into headers in `includes/` and implementations in `sources/`:
- `includes/stuff.hpp` and `sources/stuff.cpp`: constants and shared utilities
- `includes/transactions.hpp` and `sources/transactions.cpp`: transaction records
- `includes/accounts.hpp` and `sources/accounts.cpp`: base, savings, and checking accounts
- `includes/bank.hpp` and `sources/bank.cpp`: account management and persistence
- `main.cpp`: command-line application
Build with `make`, then run `./bank-account`. Account data is stored in
`accounts.txt` in the current working directory.