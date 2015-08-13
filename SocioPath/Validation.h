#ifndef Validation_h
#define Validation_h
#include "User.h"
#include "User_list.h"

typedef enum {BAD_FRMT ,Wrong_Pass, Doesnt_Exist, LOGIN_GOOD, EXIT} logIn_state;

typedef struct Validation_t{
	User_list* head;
}Validation;

void addUser(Validation *valid, User *usr);
Validation* createValidation();
User* getUser(Validation *valid, char* username);
int ValidationUserCount(Validation *valid);
void serializeValid(Validation *valid, char *PATH);
void deserializeValid(Validation *valid, char *PATH);
void CreateAccount(Validation *valid, char *username, char *password, char *securityAns);
logIn_state logIn(Validation *valid, char *username, char* pass);

#endif