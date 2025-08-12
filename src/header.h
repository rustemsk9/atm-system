#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[20];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
int initMenu(struct User *u);
void loginMenu(char a[50], char pass[50]);
// void registerMenu(char a[50], char pass[50]); // why is this not a struct User?
void registerMenu(struct User *u);
const char *getPassword(struct User u);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
void unsuccess(struct User u, int num);
void success(struct User u);
void updateAccount(struct User u);
void makeTransaction(struct User u);
void checkDetails(struct User u);
void removeAccount(struct User u);
void transactionFunctionality(struct User u, int opt, int transactionType);
void stayOrReturn(int notGood, void f(struct User u), struct User u);