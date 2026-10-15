# Bank Account and Transaction Management System in C

## 1. Project Description

The Bank Account and Transaction Management System is a menu-driven C programming project designed to manage customer bank accounts and perform basic banking operations.

The project allows users to create accounts, deposit money, withdraw money, transfer money between accounts, check account balances, and view transaction history.

It uses file handling to store account and transaction information permanently. Therefore, the data remains available even after closing the program.

## 2. Objectives

- To manage customer bank account details.
- To perform basic banking transactions.
- To maintain transaction history.
- To store data permanently using files.
- To understand structures, functions, and file handling in C.
- To develop a modular application using multiple source files.

## 3. Technologies Used

- Programming Language: C
- Compiler: GCC
- Concepts: Structures, Functions, File Handling, Strings, Loops, Conditional Statements, Switch-Case
- File Operations: `fopen()`, `fclose()`, `fread()`, `fwrite()`, `fseek()`, `rewind()`, `remove()`, `rename()`

## 4. Project Structure

```text
Bank_Management/
|
|-- main.c
|-- bank.h
|-- account.c
|-- transaction.c
|-- README.txt
|-- accounts.dat
|-- transactions.dat
```

### File Descriptions

- **main.c:** Displays the menu and handles user choices.
- **bank.h:** Contains structure definitions, constants, and function declarations.
- **account.c:** Handles account creation, display, balance checking, searching, updating, and deletion.
- **transaction.c:** Handles deposits, withdrawals, money transfers, and transaction history.
- **README.txt:** Contains project documentation.
- **accounts.dat:** Stores customer account details. Created automatically when accounts are saved.
- **transactions.dat:** Stores transaction records. Created automatically when transactions are saved.

## 5. Features

1. Create a new bank account.
2. Display account details.
3. Deposit money.
4. Withdraw money.
5. Transfer money between accounts.
6. Check account balance.
7. View transaction history.
8. Search for an account by customer name.
9. Update account details.
10. Delete an account.
11. Exit the application.

## 6. How to Compile

Make sure GCC is installed on your system.

Open the terminal in the project directory and execute:

```bash
gcc main.c account.c transaction.c -o bank
```

## 7. How to Run

On Linux:

```bash
./bank
```

On Windows using GCC/MinGW:

```bash
gcc main.c account.c transaction.c -o bank.exe
bank.exe
```

## 8. Data Storage

The project uses binary files to store information.

- `accounts.dat` stores account numbers, customer names, phone numbers, addresses, and balances.
- `transactions.dat` stores account numbers, transaction types, amounts, and balances after transactions.

The program uses file operations to read, write, update, and delete account records.

## 9. Concepts Learned

Through this project, I learned how to:

- Use structures to group related data.
- Divide a program into multiple source files.
- Use header files to share declarations.
- Perform file handling in C.
- Implement deposit, withdrawal, and transfer operations.
- Validate account numbers and transaction amounts.
- Maintain transaction records.
- Build a menu-driven application using switch-case.

## 10. Limitations

- This is an educational mini project, not a production banking application.
- It does not implement user authentication or encrypted storage.
- Transactions do not include date and time information.
- It does not support simultaneous users or concurrent transactions.

## 11. Conclusion

The Bank Account and Transaction Management System demonstrates the practical use of C programming concepts to develop a simple banking application. It provides basic account management and transaction features while using file handling to preserve data between program executions.

This project helped me improve my understanding of structures, functions, modular programming, and file handling in C.
