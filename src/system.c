#include "header.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>
const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r, int opt)
{
    int result = fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
        &r->id,
        &r->userId,
        name, // userName[50]
        &r->accountNbr,
        &r->deposit.month,
        &r->deposit.day,
        &r->deposit.year,
        r->country,
        &r->phone,
        &r->amount,
        r->accountType);
        
        // printf("Read record: ID=%d, UserID=%d, Name=%s, AccountNbr=%d, DepositDate=%d/%d/%d, Country=%s, Phone=%d, Amount=%.2lf, AccountType=%s\n",
        //     r->id,
        //     r->userId,
        //     name,
        //     r->accountNbr,
        //     r->deposit.month,
        //     r->deposit.day,
        //     r->deposit.year,
        //     r->country,
        //     r->phone,
        //     r->amount,
        //     r->accountType);

            // Proper ID validation
            if (result == EOF) {
                return 0; // End of file reached
            }
            if (result != 11) { // TODO: after 
                printf("Error: Invalid record format in file\n");
                return 0; // Incomplete record
            }
            
            // Validate ID ranges
            if (r->id < 0) {
                printf("Error: Invalid record ID (%d) - must be non-negative\n", r->id);
                return 0;
            }
            
            if (r->userId < 0) {
                printf("Error: Invalid user ID (%d) - must be non-negative\n", r->userId);
                return 0;
            }
            
            if (r->accountNbr <= 0) {
                printf("Error: Invalid account number (%d) - must be positive\n", r->accountNbr);
                return 0;
            }
            
            return 1; // Success

    // return 1; // Success
}

void makeTransaction(struct User u)
{
    system("clear");
    printf("\t\t\t===== Make Transaction =====\n");
    int option;
    printf("\nEnter your account number: ");
    scanf("%d", &option);
    if (option <= 0) {
        printf("Invalid account number!\n");
        unsuccess(u, 4);
        return;
    }

    printf("\nChoose the type of transaction:\n");
    printf("\n\t[1] - Widthdraw\n");
    printf("\n\t[2] - Deposit\n");
    printf("\n\t[3] - Exit\n");
    int option2;
    scanf("%d", &option2);

    switch (option2)
    {    
    case 1:
        // nWithdraw logic here
        // printf("\nWithdraw functionality is not implemented yet.\n");
        transactionFunctionality(u, option, option2);
        // success(u);
        break;
    case 2:
        // Deposit logic here
        // printf("\nDeposit functionality is not implemented yet.\n");
        transactionFunctionality(u, option, option2);
        success(u);
        break;
    case 3:
        // Exit logic here
        printf("\nExiting transaction menu.\n");
        // success(u);
        break;
    default:
        printf("\nInvalid option selected!\n");
        unsuccess(u, 4);
        break;
    }

}

void removeAccount(struct User u)
{
    struct Record r;
    char userName[100];
    int accNbr;

    FILE *pf = fopen(RECORDS, "r+"); // Open for reading and writing
    FILE *temp = fopen("./data/temp.txt", "w"); // Temporary file for updates
    if (pf == NULL || temp == NULL) {
        printf("Error: Unable to open file %s\n", RECORDS);
        unsuccess(u, 0);
        return;
    }

    system("clear");
    printf("\t\t\t===== Remove Account =====\n");

    printf("\nEnter your account number you want to remove: ");
    scanf("%d", &accNbr);

    int found = 0;
    // Search for the record to remove
    while (getAccountFromFile(pf, userName, &r, 0)) {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accNbr) {
            found = 1; // Record found
            continue; // Skip writing this record to the temp file
        }
        // Write the record to the temp file if it's not the one to be removed
        fprintf(temp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                r.id, r.userId, userName, r.accountNbr,
                r.deposit.month, r.deposit.day, r.deposit.year,
                r.country, r.phone, r.amount, r.accountType);
    }

    fclose(pf);
    fclose(temp);

    if (found) {
        remove(RECORDS);               // Delete the original file
        rename("./data/temp.txt", RECORDS);  // Replace with the temp file
        printf("Account removed successfully!\n");
        success(u);
    } else {
        remove("./data/temp.txt");     // Clean up temp file
        printf("Record not found.\n");
        unsuccess(u, 6);
    }
}

void checkDetails(struct User u)
{
    struct Record r;
    char userName[100];
    int accNbr;

    FILE *pf = fopen(RECORDS, "r");
    int found = 0;
    if (pf == NULL) {
        printf("Error: Unable to open file %s\n", RECORDS);
        unsuccess(u,0);
        return;
    }

    system("clear");
    printf("\t\t\t===== Check Details =====\n");

    printf("\nEnter the account number you want to check: ");
    scanf("%d", &accNbr);

    while (getAccountFromFile(pf, userName, &r, 0)) {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accNbr) {
            found = 1; // Record found
            printf("\nAccount number: %d\nDeposit Date: %d/%d/%d\nCountry: %s\nPhone number: %d\nAmount deposited: $%.2f\nType Of Account: %s\n",
                   r.accountNbr,
                   r.deposit.month,
                   r.deposit.day,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
            // fclose(pf);
            // success(u);
            // return;
            
                if (strcmp(r.accountType, saving) == 0) {
                    printf("\n\tYou will get $%.2f as interest on day %d of every month\n", r.amount * 0.07, r.deposit.day);
                // printf("\nThis is a saving account.\n");
                } else if (strcmp(r.accountType, fixed01) == 0) {
                    printf("\n\tYou will get $%.2f as interest on day %d of every month\n", r.amount * 0.04, r.deposit.day);
                    break;
                    // printf("\nThis is a fixed01 account.\n");
                } else if (strcmp(r.accountType, fixed02) == 0) {
                    printf("\n\tYou will get $%.2f as interest on day %d of every month\n", r.amount * 0.05, r.deposit.day);
                    break;
                    // printf("\nThis is a fixed02 account.\n");
                } else if (strcmp(r.accountType, fixed03) == 0) {
                    printf("\n\tYou will get $%.2f as interest on day %d of every month\n", r.amount * 0.08, r.deposit.day);
                    break;
                    // printf("\nThis is a fixed03 account.\n");
                } else if (strcmp(r.accountType, current) == 0) {
                    printf("\n\tYou will not get any interest on this account.\n");
                    break;
                    
                    // printf("\nThis is a current account.\n");
                } else {
                    printf("\nInvalid account type!\n");
                    break; // Invalid account type
                }

            break; // Exit the loop after finding the record
        }
    }
    
    if (found) {
        fclose(pf);
        success(u);
        return;
    } else {
        fclose(pf);
        printf("Record not found.\n");
        unsuccess(u,5);

    }
}

int checkAccountType(char accountType[20])
{
    if (strcmp(accountType, saving) == 0) {
        return 0;
        // printf("\nThis is a saving account.\n");
    } else if (strcmp(accountType, fixed01) == 0) {
        return 1;
        // printf("\nThis is a fixed01 account.\n");
    } else if (strcmp(accountType, fixed02) == 0) {
        return 2;
        // printf("\nThis is a fixed02 account.\n");
    } else if (strcmp(accountType, fixed03) == 0) {
        return 3;
        // printf("\nThis is a fixed03 account.\n");
    } else if (strcmp(accountType, current) == 0) {
        return 4;
        // printf("\nThis is a current account.\n");
    } else {
        printf("\nInvalid account type!\n");
        return -1; // Invalid account type
    }
}
void transactionFunctionality(struct User u, int opt, int transactionType) 
{
    struct Record r;

    FILE *pf = fopen(RECORDS, "r+");  // Use r+ for read/write
    FILE *temp = fopen("./data/temp.txt", "w"); // Temporary file for updates
    if (pf == NULL || temp == NULL) {
        printf("Error: Unable to open file %s\n", RECORDS);
        unsuccess(u, 0);
        return;
    }

    // need to retrieve info and edit it
    int phone;
    char country[100];
    int found = 0;
    long position;
    char userName[100];

    if (transactionType == 1) {
        // Deposit logic here
        printf("\nWithdraw functionality is not implemented yet.\n");
        while (fscanf(pf, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                        &r.id, &r.userId, userName, &r.accountNbr,
                        &r.deposit.month, &r.deposit.day, &r.deposit.year,
                        r.country, &r.phone, &r.amount, r.accountType) == 11) {
                double new_amount;
                double tmp = r.amount; // Initialize new_amount with current amount
                if (strcmp(userName, u.name) == 0 && r.accountNbr == opt) {
                    switch (checkAccountType(r.accountType)){
                        case 1:
                        printf("\nYou cannot withdraw from a fixed01 account.\n");
                        case 2:
                        printf("\nYou cannot withdraw from a fixed02 account.\n");
                        case 3:
                        printf("\nYou cannot withdraw from a fixed03 account.\n");
                        fclose(pf);
                        fclose(temp);
                        return;
                    }
                    found = 1;
                    // printf("\nRecord found! Current Phone: %d, Country: %s\n", r.phone, r.country);
                    int opt1;

                    invalid2:
                    printf("\nEnter the ammount you want to withdraw: $");
                    scanf("%lf", &new_amount);
                    if (new_amount > r.amount) {
                        int opt_re1 = 0;
                        printf("Insufficient funds! Current amount: $%.2lf\n", r.amount);
                        printf("\n[1] Enter the new amount to withdraw");
                        printf("\n[2] Back to main transaction menu");
                        printf("\n[3] Exit");
                        scanf("%d", &opt_re1);
                        switch (opt_re1) {
                        case 1:
                            goto invalid2;
                            // printf("\nEnter the new amount to withdraw: ");
                            // scanf("%d", &new_amount);
                            break;
                        case 2:
                            printf("\nBack to main transaction menu.\n");
                            makeTransaction(u);
                            fclose(pf);
                            fclose(temp);
                            // success(u);
                            return;
                        case 3:
                            printf("\nExiting transaction menu.\n");
                            fclose(pf);
                            fclose(temp);
                            // success(u);
                            return;
                        }                                
                    } else {
                        tmp = r.amount - new_amount;
                    }
                }
                // Pad Records to Fixed Length
                // If you want to overwrite the file in place,
                // fprintf(pf, "%-10d %-10d %-20s %-10d %-2d/%-2d/%-4d %-20s %-10d %-10.2lf %-10s\n",
                // r.id, r.userId, userName, r.accountNbr,
                // r.deposit.month, r.deposit.day, r.deposit.year,
                // r.country, r.phone, r.amount, r.accountType);
                // Write the (updated or original) record to the temp file

                fprintf(temp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                        r.id, r.userId, userName, r.accountNbr,
                        r.deposit.month, r.deposit.day, r.deposit.year,
                        r.country, r.phone, tmp, r.accountType);
            }

        fclose(pf);
        fclose(temp);   
        if (found) {
            remove(RECORDS);               // Delete the original file
            rename("./data/temp.txt", RECORDS);  // Replace with the temp file
            printf("Transaction completed successfully!\n");
            success(u);
            return;
        } else {
            remove("./data/temp.txt");     // Clean up temp file
            printf("Record not found.\n");
            unsuccess(u, 4);
            return;
        }
    } else if (transactionType == 2) {
        // Deposit logic here
        printf("\nDeposit functionality is not implemented yet.\n");
        while (fscanf(pf, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                        &r.id, &r.userId, userName, &r.accountNbr,
                        &r.deposit.month, &r.deposit.day, &r.deposit.year,
                        r.country, &r.phone, &r.amount, r.accountType) == 11) {
                            
                double new_amount;
                double tmp = r.amount; // Initialize new_amount with current amount
                if (strcmp(userName, u.name) == 0 && r.accountNbr == opt) {
                    found = 1;
                    // printf("\nRecord found! Current Phone: %d, Country: %s\n", r.phone, r.country);
                    int opt1;

                    invalid:
                    printf("\nEnter the ammount you want to deposit: $");
                    scanf("%2lf", &new_amount);
                    tmp += new_amount; // Add the deposit amount to the current amount
                }
                // Pad Records to Fixed Length
                // If you want to overwrite the file in place,
                // fprintf(pf, "%-10d %-10d %-20s %-10d %-2d/%-2d/%-4d %-20s %-10d %-10.2lf %-10s\n",
                // r.id, r.userId, userName, r.accountNbr,
                // r.deposit.month, r.deposit.day, r.deposit.year,
                // r.country, r.phone, r.amount, r.accountType);
                // Write the (updated or original) record to the temp file

                fprintf(temp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                        r.id, r.userId, userName, r.accountNbr,
                        r.deposit.month, r.deposit.day, r.deposit.year,
                        r.country, r.phone, tmp, r.accountType);
            }

        fclose(pf);
        fclose(temp);   
        if (found) {
            remove(RECORDS);               // Delete the original file
            rename("./data/temp.txt", RECORDS);  // Replace with the temp file
            // printf("Transaction completed successfully!\n");
            success(u);
            // return;
            // stayOrReturn(1, makeTransaction, u);
        } else {
            remove("./data/temp.txt");     // Clean up temp file
            printf("Record not found.\n");
            unsuccess(u, 4);
            // return;
        }
        // success(u);
    } else {
        // Exit logic here
        printf("\nExiting transaction menu.\n");
        success(u);
        // return;
    }
}
void updateAccount(struct User u)
{
    struct Record r;

    FILE *pf = fopen(RECORDS, "r+");  // Use r+ for read/write
    FILE *temp = fopen("./data/temp.txt", "w"); // Temporary file for updates
    if (pf == NULL || temp == NULL) {
        printf("Error: Unable to open file %s\n", RECORDS);
        unsuccess(u, 0);
        return;
    }
    system("clear");
    printf("\t\t\t===== Update record =====\n");

    int accToUpdate;
    printf("\nWhat is the account number you want to update:");
    scanf("%d", &accToUpdate); // is it Itoa?
    printf("You want to update account number: %d\n", accToUpdate);

    // need to retrieve info and edit it
    int opt1;
    int phone;
    char country[100];
    int found = 0;
    long position;
    char userName[100];
    int opt2 = 0;
    // Search for the record
    while (fscanf(pf, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r.id, &r.userId, userName, &r.accountNbr,
                  &r.deposit.month, &r.deposit.day, &r.deposit.year,
                  r.country, &r.phone, &r.amount, r.accountType) == 11) {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accToUpdate) {
            found = 1;
            printf("\nRecord found! Current Phone: %d, Country: %s\n", r.phone, r.country);

            int opt1;
            printf("\nWhich information do you want to update:\n1: Phone number\n2: Country\nChoice: ");
            scanf("%d", &opt1);

            if (opt1 == 1) {
                printf("\nEnter the new phone number: ");
                scanf("%d", &r.phone);
            } else if (opt1 == 2) {
                printf("\nEnter the new country: ");
                scanf("%s", r.country);
            } else {
                printf("Invalid option selected.\n");
                fclose(pf);
                fclose(temp);
                return;
            }
        }
        // Pad Records to Fixed Length
        // If you want to overwrite the file in place,
        // fprintf(pf, "%-10d %-10d %-20s %-10d %-2d/%-2d/%-4d %-20s %-10d %-10.2lf %-10s\n",
        // r.id, r.userId, userName, r.accountNbr,
        // r.deposit.month, r.deposit.day, r.deposit.year,
        // r.country, r.phone, r.amount, r.accountType);
        // Write the (updated or original) record to the temp file
        fprintf(temp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                r.id, r.userId, userName, r.accountNbr,
                r.deposit.month, r.deposit.day, r.deposit.year,
                r.country, r.phone, r.amount, r.accountType);
    }
        // printf("Read record: ID=%d, UserID=%d, Name=%s, AccountNbr=%d, DepositDate=%d/%d/%d, Country=%s, Phone=%d, Amount=%lf, AccountType=%s\n",
        //         r.id,
        //         r.userId,
        //         userName,
        //         r.accountNbr,
        //         r.deposit.month,
        //         r.deposit.day,
        //         r.deposit.year,
        //         r.country,
        //         r.phone,
        //         r.amount,
        //         r.accountType);
    

    fclose(pf);
    fclose(temp);
    if (found) {
        remove(RECORDS);               // Delete the original file
        rename("./data/temp.txt", RECORDS);  // Replace with the temp file
        // printf("Record updated successfully!\n");
        success(u);
    } else {
        remove("./data/temp.txt");     // Clean up temp file
        printf("Record not found.\n");
        unsuccess(u, 2);
    }
    // fclose(pf);
    // success(u);
}
void saveAccountToFile(FILE *ptr, struct User u, struct Record r, int id)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
            id, // Use the provided ID or auto-increment logic
	        u.id,
	        u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day, // auto 1
            r.deposit.year, // auto -2062028388
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void unsuccess(struct User u, int num)
{
    int option;
    printf("\n✖ Unsuccessful!\n\n");
invalid:
    printf("Enter 1 to try again, and 0 to exit:");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        switch (num) {
            case 1:
                createNewAcc(u);
                break;
            case 2:
                updateAccount(u);
                break;
            case 3:
                checkAllAccounts(u);
                break;
            case 4:
                makeTransaction(u);
                break;
            case 5:
                checkDetails(u);
                break;
            case 6:
                removeAccount(u);
                break;
            default:
                initMenu(&u);
        }
        
    } 
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+"); // Open for appending and reading
    
    if (pf == NULL) {
        printf("Error: Unable to open file %s\n", RECORDS);
        unsuccess(u, 1);
        return;
    }
    int num = 0;
    // while(fscanf(pf, "%d %d %s %d %d/%d/%d %s %d %lf %s",
    //               &r.id, &r.userId, userName, &r.accountNbr,
    //               &r.deposit.month, &r.deposit.day, &r.deposit.year,
    //               r.country, &r.phone, &r.amount, r.accountType) == 11) {
    //     num = r.id;
    // }
noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
enterAgain:
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    rewind(pf);
    while (getAccountFromFile(pf, userName, &cr, 0))
    {
        num++;
        // printf("OMG: %d\n", num);
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            num = 0;
            goto enterAgain;
        }
    }

    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);

    saveAccountToFile(pf, u, r, num + 1); // Use num + 1 as the new ID

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u) // for records.txt
{
    char userName[100];
    struct Record r;
    int found = 0;
    FILE *pf = fopen(RECORDS, "r");
    
    if (pf == NULL) {
        printf("Error: Unable to open file %s\n", RECORDS);
        unsuccess(u, 0);
        return;
    }

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r, 0)) // user 10, but shows 12
    {
        if (strcmp(userName, u.name) == 0)
        {
            found = 1; // Record found
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
        // printf("Read record: ID=%d, UserID=%d, Name=%s, AccountNbr=%d, DepositDate=%d/%d/%d, Country=%s, Phone=%d, Amount=%.2lf, AccountType=%s\n",
    }
    fclose(pf);
    if (found) {
        success(u);
    } else {
        unsuccess(u, 0);
    }
}
