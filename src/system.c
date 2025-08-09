#include "header.h"

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r, int opt)
{
    if (opt == 0) {
        int result = fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
            &r->id,
            &r->userId,
            name,
            &r->accountNbr,
            &r->deposit.month,
            &r->deposit.day,
            &r->deposit.year,
            r->country,
            &r->phone,
            &r->amount,
            r->accountType);
            
            printf("Read record: ID=%d, UserID=%d, Name=%s, AccountNbr=%d, DepositDate=%d/%d/%d, Country=%s, Phone=%d, Amount=%.2lf, AccountType=%s\n",
                r->id,
                r->userId,
                name,
                r->accountNbr,
                r->deposit.month,
                r->deposit.day,
                r->deposit.year,
                r->country,
                r->phone,
                r->amount,
                r->accountType);
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
            } else if (opt == 1) { // needbyAccountNbr
                    
            

    }
    return 1; // Success
}

// void editRecord(FILE *ptr, char name[50], int accNbr) {

//     int result = fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
//                        &r->id,
//                        &r->userId,
//                        name,
//                        &r->accountNbr,
//                     &r->deposit.month,
//                     &r->deposit.day,
//                     &r->deposit.year,
//                     r->country,
//                     &r->phone,
//                     &r->amount,
//                     r->accountType);
    
// }
void makeTransaction(struct User u)
{
    system("clear");
    printf("\t\t\t===== Make Transaction =====\n");

}

void updateAccount(struct User u)
{
    struct Record r;

    FILE *pf = fopen(RECORDS, "a+");  // Use r+ for read/write

    if (pf == NULL) {
        printf("Error: Unable to open file %s\n", RECORDS);
        unsuccess(u);
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
    char userName[50];
    // Search for the record
    while (!feof(pf)) {
        position = ftell(pf);  // Track the current position
        int result = fscanf(pf, "%d %d %s %d %d/%d/%d %s %d %.2lf %s",
                            &r.id, &r.userId, "21", &r.accountNbr,
                            &r.deposit.month, &r.deposit.day, &r.deposit.year,
                            r.country, &r.phone, &r.amount, r.accountType);
            // if (result != 11) {
            //     printf("Error: Malformed record\n");
            //     continue;  // Skip to the next record
            // }
        printf("Read record: ID=%d, UserID=%d, Name=%s, AccountNbr=%d, DepositDate=%d/%d/%d, Country=%s, Phone=%d, Amount=%.2lf, AccountType=%s\n",
                r.id,
                r.userId,
                userName,
                r.accountNbr,
                r.deposit.month,
                r.deposit.day,
                r.deposit.year,
                r.country,
                r.phone,
                r.amount,
                r.accountType);
        if (result == EOF) break;
        if (result != 11) continue;  // Skip malformed records

        // Check if this is the record to edit
        if (strcmp(userName, u.name) == 0 && r.accountNbr == (int)accToUpdate) {
            found = 1;
            break;
        }
    }
    if (found) {
        printf("\n Which information do you want to update:\n1: Phone number:(%d)\n2: Country:(%s): ", r.phone, r.country);
        scanf("%d", &opt1);
        if (opt1 == 1) {
            printf("\nEnter the new phone number:");
            scanf("%d", &phone);
            r.phone = phone;

        } else if (opt1 == 2) {
            printf("\nEnter the new country:");
            scanf("%s", country);
            strcpy(r.country, country);
        } else {
            printf("Invalid option selected.\n");
            fclose(pf);
            return;
        }
        
        // Proceed with the transaction
    } else {
        printf("Record not found for user %s with account number %d.\n", u.name, r.accountNbr);
        fclose(pf);
        return;
    }
}
void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
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

void unsuccess(struct User u)
{
    int option;
    printf("\n✖ Unsuccessful!\n\n");
invalid:
    printf("Enter 1 to try again, and 0 to exit:");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        initMenu(&u);
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
    FILE *pf = fopen(RECORDS, "a+");
    
    if (pf == NULL) {
        printf("Error: Unable to open file %s\n", RECORDS);
        unsuccess(u);
        return;
    }

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
enterAgain:
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, userName, &cr, 0))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
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

    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u) // for records.txt
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");
    
    if (pf == NULL) {
        printf("Error: Unable to open file %s\n", RECORDS);
        unsuccess(u);
        return;
    }

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r, 0)) // user 10, but shows 12
    {
        if (strcmp(userName, u.name) == 0)
        {
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
    }
    fclose(pf);
    success(u);
}
