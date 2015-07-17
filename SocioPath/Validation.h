#ifndef Validation_h
#define Validation_h
#include "User.h"
#include "User_list.h"

typedef enum {Wrong_Pass, Doesnt_Exist, GOOD} logIn_state;

typedef struct Validation_t{
	User_list* head;
}Validation;

void addUser(Validation *valid, User *usr);
Validation* createValidation(User_list *user_list);
User* getUser(Validation *valid, char* username);
void serializeValid(Validation *valid, char *PATH);
void deserializeValid(Validation *valid, char *PATH);
void CreateAccount(Validation *valid, char *username, char *password, char *securityAns);
logIn_state logIn(Validation *valid, char *username, char* pass);

#endif