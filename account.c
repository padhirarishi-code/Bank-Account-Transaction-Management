#include "bank.h"


/* Check whether account exists */
int accountExists(int accountNo)
{
    FILE *fp;
    struct Account acc;

    fp = fopen(ACCOUNT_FILE, "rb");

    if (fp == NULL)
    {
        return 0;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp) == 1)
    {
        if (acc.accountNo == accountNo)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}


/* 1. Create Account */
void createAccount()
{
    FILE *fp;
    struct Account acc;

    printf("\n========== CREATE ACCOUNT ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &acc.accountNo);

    if (accountExists(acc.accountNo))
    {
        printf("Account number already exists.\n");
        return;
    }

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", acc.name);

    printf("Enter Phone Number: ");
    scanf("%14s", acc.phone);

    printf("Enter Address: ");
    scanf(" %[^\n]", acc.address);

    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    if (acc.balance < 0)
    {
        printf("Initial balance cannot be negative.\n");
        return;
    }

    fp = fopen(ACCOUNT_FILE, "ab");

    if (fp == NULL)
    {
        printf("Unable to open account file.\n");
        return;
    }

    fwrite(&acc, sizeof(struct Account), 1, fp);

    fclose(fp);

    printf("\nAccount created successfully!\n");
}


/* 2. Display Account */
void displayAccount()
{
    FILE *fp;
    struct Account acc;
    int accountNo;
    int found = 0;

    printf("\n========== DISPLAY ACCOUNT ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNo);

    fp = fopen(ACCOUNT_FILE, "rb");

    if (fp == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp) == 1)
    {
        if (acc.accountNo == accountNo)
        {
            printf("\nAccount Number : %d\n", acc.accountNo);
            printf("Name           : %s\n", acc.name);
            printf("Phone          : %s\n", acc.phone);
            printf("Address        : %s\n", acc.address);
            printf("Balance        : %.2f\n", acc.balance);

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


/* 6. Check Balance */
void checkBalance()
{
    FILE *fp;
    struct Account acc;
    int accountNo;
    int found = 0;

    printf("\n========== CHECK BALANCE ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNo);

    fp = fopen(ACCOUNT_FILE, "rb");

    if (fp == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp) == 1)
    {
        if (acc.accountNo == accountNo)
        {
            printf("\nAccount Number : %d\n", acc.accountNo);
            printf("Account Holder : %s\n", acc.name);
            printf("Balance        : %.2f\n", acc.balance);

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


/* 8. Search Account */
void searchAccount()
{
    FILE *fp;
    struct Account acc;
    char name[50];
    int found = 0;

    printf("\n========== SEARCH ACCOUNT ==========\n");

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", name);

    fp = fopen(ACCOUNT_FILE, "rb");

    if (fp == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp) == 1)
    {
        if (strcmp(acc.name, name) == 0)
        {
            printf("\nAccount Number : %d\n", acc.accountNo);
            printf("Name           : %s\n", acc.name);
            printf("Phone          : %s\n", acc.phone);
            printf("Address        : %s\n", acc.address);
            printf("Balance        : %.2f\n", acc.balance);

            found = 1;
        }
    }

    fclose(fp);

    if (found == 0)
    {
        printf("Account not found.\n");
    }
}


/* 9. Update Account */
void updateAccount()
{
    FILE *fp;
    struct Account acc;
    int accountNo;
    int found = 0;

    printf("\n========== UPDATE ACCOUNT ==========\n");

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
            printf("\nCurrent Details:\n");
            printf("Name    : %s\n", acc.name);
            printf("Phone   : %s\n", acc.phone);
            printf("Address : %s\n", acc.address);

            printf("\nEnter New Name: ");
            scanf(" %[^\n]", acc.name);

            printf("Enter New Phone: ");
            scanf("%14s", acc.phone);

            printf("Enter New Address: ");
            scanf(" %[^\n]", acc.address);

            fseek(fp, -sizeof(struct Account), SEEK_CUR);

            fwrite(&acc, sizeof(struct Account), 1, fp);

            printf("\nAccount updated successfully.\n");

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


/* 10. Delete Account */
void deleteAccount()
{
    FILE *fp;
    FILE *temp;
    struct Account acc;
    int accountNo;
    int found = 0;

    printf("\n========== DELETE ACCOUNT ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNo);

    fp = fopen(ACCOUNT_FILE, "rb");

    if (fp == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    if (temp == NULL)
    {
        printf("Unable to create temporary file.\n");
        fclose(fp);
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp) == 1)
    {
        if (acc.accountNo == accountNo)
        {
            found = 1;
        }
        else
        {
            fwrite(&acc, sizeof(struct Account), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found == 1)
    {
        remove(ACCOUNT_FILE);
        rename("temp.dat", ACCOUNT_FILE);

        printf("Account deleted successfully.\n");
    }
    else
    {
        remove("temp.dat");

        printf("Account not found.\n");
    }
}