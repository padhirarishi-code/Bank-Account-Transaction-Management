#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCOUNT_FILE "accounts.dat"
#define TRANSACTION_FILE "transactions.dat"

/* Account structure */
struct Account
{
    int accountNo;
    char name[50];
    char phone[15];
    char address[100];
    float balance;
};

/* Transaction structure */
struct Transaction
{
    int accountNo;
    char type[30];
    float amount;
    float balance;
};

/* Account functions */
void createAccount();
void displayAccount();
void checkBalance();
void searchAccount();
void updateAccount();
void deleteAccount();

int accountExists(int accountNo);

/* Transaction functions */
void depositMoney();
void withdrawMoney();
void transferMoney();
void transactionHistory();

void saveTransaction(int accountNo,
                     const char type[],
                     float amount,
                     float balance);

#endif