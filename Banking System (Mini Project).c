
#include <stdio.h>
#include <stdlib.h>

#define BANK_FILE "bank.dat"

typedef struct {
    int accountNo;
    char name[50];
    double balance;
} Account;

int findAccount(FILE *fp, int accountNo, Account *a) {
    rewind(fp);

    while (fread(a, sizeof(Account), 1, fp) == 1) {
        if (a->accountNo == accountNo)
            return 1;
    }

    return 0;
}

void createAccount(void) {
    FILE *fp = fopen(BANK_FILE, "ab+");
    Account a, temp;

    if (fp == NULL) {
        printf("Unable to open bank file!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &a.accountNo);

    if (findAccount(fp, a.accountNo, &temp)) {
        printf("Account number already exists!\n");
        fclose(fp);
        return;
    }

    printf("Enter account holder name (one word): ");
    scanf("%49s", a.name);

    printf("Enter opening balance: ");
    scanf("%lf", &a.balance);

    if (a.balance < 0) {
        printf("Balance cannot be negative!\n");
        fclose(fp);
        return;
    }

    fseek(fp, 0, SEEK_END);
    fwrite(&a, sizeof(Account), 1, fp);

    fclose(fp);
    printf("Account created successfully!\n");
}

void deposit(void) {
    FILE *fp = fopen(BANK_FILE, "rb+");
    Account a;
    int accountNo;
    double amount;

    if (fp == NULL) {
        printf("Bank records not found!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &accountNo);

    if (!findAccount(fp, accountNo, &a)) {
        printf("Account not found!\n");
        fclose(fp);
        return;
    }

    printf("Enter deposit amount: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Amount must be positive!\n");
        fclose(fp);
        return;
    }

    a.balance += amount;

    fseek(fp, -(long)sizeof(Account), SEEK_CUR);
    fwrite(&a, sizeof(Account), 1, fp);

    fclose(fp);
    printf("Deposit successful!\n");
    printf("New balance: %.2f\n", a.balance);
}

void withdraw(void) {
    FILE *fp = fopen(BANK_FILE, "rb+");
    Account a;
    int accountNo;
    double amount;

    if (fp == NULL) {
        printf("Bank records not found!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &accountNo);

    if (!findAccount(fp, accountNo, &a)) {
        printf("Account not found!\n");
        fclose(fp);
        return;
    }

    printf("Enter withdrawal amount: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Amount must be positive!\n");
        fclose(fp);
        return;
    }

    if (amount > a.balance) {
        printf("Insufficient balance!\n");
        fclose(fp);
        return;
    }

    a.balance -= amount;

    fseek(fp, -(long)sizeof(Account), SEEK_CUR);
    fwrite(&a, sizeof(Account), 1, fp);

    fclose(fp);
    printf("Withdrawal successful!\n");
    printf("Remaining balance: %.2f\n", a.balance);
}

void checkBalance(void) {
    FILE *fp = fopen(BANK_FILE, "rb");
    Account a;
    int accountNo;

    if (fp == NULL) {
        printf("Bank records not found!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &accountNo);

    if (findAccount(fp, accountNo, &a)) {
        printf("\nAccount Number: %d\n", a.accountNo);
        printf("Account Holder: %s\n", a.name);
        printf("Available Balance: %.2f\n", a.balance);
    } else {
        printf("Account not found!\n");
    }

    fclose(fp);
}

void displayAccounts(void) {
    FILE *fp = fopen(BANK_FILE, "rb");
    Account a;
    int found = 0;

    if (fp == NULL) {
        printf("No bank records found!\n");
        return;
    }

    printf("\n===== ALL BANK ACCOUNTS =====\n");

    while (fread(&a, sizeof(Account), 1, fp) == 1) {
        printf("Account: %d | Name: %s | Balance: %.2f\n",
               a.accountNo, a.name, a.balance);
        found = 1;
    }

    if (!found)
        printf("No accounts available.\n");

    fclose(fp);
}

int main(void) {
    int choice;

    do {
        printf("\n===== BANKING SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Display All Accounts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            return 1;
        }

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: displayAccounts(); break;
            case 6: printf("Thank you for using our bank!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}