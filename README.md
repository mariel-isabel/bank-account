# bank-account

This project is split into headers in `includes/` and implementations in `sources/`:

- `includes/stuff.hpp` and `sources/stuff.cpp`: constants and shared utilities
- `includes/transactions.hpp` and `sources/transactions.cpp`: transaction records
- `includes/accounts.hpp` and `sources/accounts.cpp`: base, savings, and checking accounts
- `includes/bank.hpp` and `sources/bank.cpp`: account management and persistence
- `main.cpp`: command-line application

Build with `make`, then run `./bank-account`. Account data is stored in
`accounts.txt` in the current working directory.