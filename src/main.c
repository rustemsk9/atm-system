#include "header.h"

void mainMenu(struct User u)
{
    int option;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[0]- Exit\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        updateAccount(u, 0, "");
        // student TODO : add your **Update account information** function
        // here
        break;
    case 3:
        checkDetails(u, 0);
        // **Check the details of existing accounts** function
        // here
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        makeTransaction(u);
        // **Make transaction** function
        // here
        break;
    case 6:
        removeAccount(u);
        // **Remove existing account** function
        // here
        break;
    case 7:
        transferOwnership(u);
        // **Transfer ownership** function
        // here
        break;
    case 0:
        exit(1);
        break;
    default:
        printf("Invalid operation!\n");
    }
};

int initMenu(struct User *u)
{
    int r = 0;
    int option;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");
    while (!r)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(*u)) == 0)
            {
                printf("\n\nPassword Match!");
                r = 1; // if no r = 1 , while loop continues , omg
                return 1; // return success
            }
            else
            {
                printf("\nWrong password!! or User Name\n");
                unsuccess(*u, 0);
                // exit(1);
            }
            r = 1; 
            break;
        case 2:
            registerMenu(u);
            
            // student TODO : add your **Registration** function
            // here
            r = 1;
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("Insert a valid operation!\n");
        }
    }
    return 0; // return failure
};

int main()
{
    struct User u;
    
    int result = initMenu(&u);
    if (result == 1) mainMenu(u);
    return 0;
}
