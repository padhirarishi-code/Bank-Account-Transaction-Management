#include "bank.h"


/* Save transaction */
void saveTransaction(int accountNo,
                     const char type[],
                     float amount,
                     float balance)
{
    FILE *fp;
    struct Transaction t;

    fp = fopen(TRANSACTION_FILE, "ab");

    if (fp == NULL)
    {
        printf("Unable to open transaction file.\n");
        return;
    }

    t.accountNo = accountNo;

    strcpy(t.type, type);

    t.amount = amount;
    t.balance = balance;

    fwrite(&t, sizeof(struct Transaction), 1, fp);

    fclose(fp);
}


/* 3. Deposit Money */
void depositMoney()
{
    FILE *fp;
    struct Account acc;

    int accountNo;
    float amount;

    int found = 0;

    printf("\n========== DEPOSIT MONEY ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNo);

    fp = fopen(ACCOUNT_FILE, "rb+");

    if (fp == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp) == 1)
    {
        if (acc.accountNo == accountNo)
        {
            printf("Current Balance: %.2f\n", acc.balance);

            printf("Enter Deposit Amount: ");
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("Invalid amount.\n");
                fclose(fp);
                return;
            }

            acc.balance = acc.balance + amount;

            fseek(fp, -sizeof(struct Account), SEEK_CUR);

            fwrite(&acc, sizeof(struct Account), 1, fp);

            saveTransaction(
                acc.accountNo,
                "Deposit",
                amount,
                acc.balance
            );

            printf("\nAmount deposited successfully.\n");
            printf("New Balance: %.2f\n", acc.balance);

            found = 1;

            break;
        }
    }

    fclose(fp);

    if (found == 0)
    {
        printf("Account not found.\n");
    }
}


/* 4. Withdraw Money */
void withdrawMoney()
{
    FILE *fp;
    struct Account acc;

    int accountNo;
    float amount;

    int found = 0;

    printf("\n========== WITHDRAW MONEY ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNo);

    fp = fopen(ACCOUNT_FILE, "rb+");

    if (fp == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp) == 1)
    {
        if (acc.accountNo == accountNo)
        {
            printf("Current Balance: %.2f\n", acc.balance);

            printf("Enter Withdrawal Amount: ");
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("Invalid amount.\n");
                fclose(fp);
                return;
            }

            if (amount > acc.balance)
            {
                printf("Insufficient balance.\n");
                fclose(fp);
                return;
            }

            acc.balance = acc.balance - amount;

            fseek(fp, -sizeof(struct Account), SEEK_CUR);

            fwrite(&acc, sizeof(struct Account), 1, fp);

            saveTransaction(
                acc.accountNo,
                "Withdrawal",
                amount,
                acc.balance
            );

            printf("\nAmount withdrawn successfully.\n");
            printf("Remaining Balance: %.2f\n", acc.balance);

            found = 1;

            break;
        }
    }

    fclose(fp);

    if (found == 0)
    {
        printf("Account not found.\n");
    }
}


/* 5. Transfer Money */
void transferMoney()
{
    FILE *fp;

    struct Account sender;
    struct Account receiver;

    int senderNo;
    int receiverNo;

    float amount;

    long senderPosition;
    long receiverPosition;

    int senderFound = 0;
    int receiverFound = 0;


    printf("\n========== TRANSFER MONEY ==========\n");

    printf("Enter Sender Account Number: ");
    scanf("%d", &senderNo);

    printf("Enter Receiver Account Number: ");
    scanf("%d", &receiverNo);


    if (senderNo == receiverNo)
    {
        printf("Sender and receiver cannot be same.\n");
        return;
    }


    fp = fopen(ACCOUNT_FILE, "rb+");

    if (fp == NULL)
    {
        printf("No accounts found.\n");
        return;
    }


    /* Find sender */

    while (1)
    {
        senderPosition = ftell(fp);

        if (fread(&sender,
                  sizeof(struct Account),
                  1,
                  fp) != 1)
        {
            break;
        }

        if (sender.accountNo == senderNo)
        {
            senderFound = 1;
            break;
        }
    }


    /* Go back to beginning */

    rewind(fp);


    /* Find receiver */

    while (1)
    {
        receiverPosition = ftell(fp);

        if (fread(&receiver,
                  sizeof(struct Account),
                  1,
                  fp) != 1)
        {
            break;
        }

        if (receiver.accountNo == receiverNo)
        {
            receiverFound = 1;
            break;
        }
    }


    if (senderFound == 0)
    {
        printf("Sender account not found.\n");
        fclose(fp);
        return;
    }


    if (receiverFound == 0)
    {
        printf("Receiver account not found.\n");
        fclose(fp);
        return;
    }


    printf("Sender Balance: %.2f\n", sender.balance);

    printf("Enter Transfer Amount: ");
    scanf("%f", &amount);


    if (amount <= 0)
    {
        printf("Invalid amount.\n");
        fclose(fp);
        return;
    }


    if (amount > sender.balance)
    {
        printf("Insufficient balance.\n");
        fclose(fp);
        return;
    }


    /* Update balances */

    sender.balance = sender.balance - amount;

    receiver.balance = receiver.balance + amount;


    /* Update sender */

    fseek(fp, senderPosition, SEEK_SET);

    fwrite(&sender,
           sizeof(struct Account),
           1,
           fp);


    /* Update receiver */

    fseek(fp, receiverPosition, SEEK_SET);

    fwrite(&receiver,
           sizeof(struct Account),
           1,
           fp);


    fclose(fp);


    /* Save transactions */

    saveTransaction(
        sender.accountNo,
        "Transfer Sent",
        amount,
        sender.balance
    );


    saveTransaction(
        receiver.accountNo,
        "Transfer Received",
        amount,
        receiver.balance
    );


    printf("\nTransfer successful!\n");

    printf("Amount Transferred : %.2f\n", amount);

    printf("Sender Balance     : %.2f\n",
           sender.balance);

    printf("Receiver Balance   : %.2f\n",
           receiver.balance);
}


/* 7. Transaction History */
void transactionHistory()
{
    FILE *fp;
    struct Transaction t;

    int accountNo;
    int found = 0;


    printf("\n========== TRANSACTION HISTORY ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNo);


    fp = fopen(TRANSACTION_FILE, "rb");

    if (fp == NULL)
    {
        printf("No transaction history found.\n");
        return;
    }


    printf("\n");
    printf("%-15s %-20s %-15s %-15s\n",
           "Account No",
           "Transaction",
           "Amount",
           "Balance");


    printf("------------------------------------------------------------\n");


    while (fread(&t,
                 sizeof(struct Transaction),
                 1,
                 fp) == 1)
    {
        if (t.accountNo == accountNo)
        {
            printf("%-15d %-20s %-15.2f %-15.2f\n",
                   t.accountNo,
                   t.type,
                   t.amount,
                   t.balance);

            found = 1;
        }
    }


    fclose(fp);


    if (found == 0)
    {
        printf("No transactions found for this account.\n");
    }
}