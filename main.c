#include "bank.h"

int main()
{
    int choice;

    while (1)
    {
        printf("\n\n");
        printf("============================================\n");
        printf("       BANK ACCOUNT MANAGEMENT SYSTEM\n");
        printf("============================================\n");

        printf("1.  Create Account\n");
        printf("2.  Display Account\n");
        printf("3.  Deposit Money\n");
        printf("4.  Withdraw Money\n");
        printf("5.  Transfer Money\n");
        printf("6.  Check Balance\n");
        printf("7.  Transaction History\n");
        printf("8.  Search Account\n");
        printf("9.  Update Account\n");
        printf("10. Delete Account\n");
        printf("11. Exit\n");

        printf("============================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                displayAccount();
                break;

            case 3:
                depositMoney();
                break;

            case 4:
                withdrawMoney();
                break;

            case 5:
                transferMoney();
                break;

            case 6:
                checkBalance();
                break;

            case 7:
                transactionHistory();
                break;

            case 8:
                searchAccount();
                break;

            case 9:
                updateAccount();
                break;

            case 10:
                deleteAccount();
                break;

            case 11:
                printf("\nThank you for using Bank Management System!\n");
                exit(0);

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}