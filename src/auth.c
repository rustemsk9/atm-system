#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";
// users
// 0 Alice 1234password
// 1 Michel password1234

// records
// 0 0 Alice 0 10/02/2020 german 986134231 11090830.00 current
// 1 1 Michel 2 10/10/2021 portugal 914134431 1920.42 savings
// 2 0 Alice 1 10/10/2000 finland 986134231 1234.21 savings
void registerMenu(struct User *u)
{
    FILE *fp;
    if ((fp = fopen(USERS, "a")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    // checkAllAccounts(*fp, a);
    // fprintf(fp, "%s %s\n", a, pass);
    fclose(fp);
    printf("\nUser registered successfully!\n");
}
void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", a);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%s %s", userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}