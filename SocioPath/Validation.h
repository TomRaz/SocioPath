#ifndef Validation_h
#define Validation_h
#include "User.h"

typedef enum {Wrong_Pass, Doesnt_Exist, GOOD} logIn_state;

typedef struct User_list_item{
	User usr;
	struct User_list_item *next;

}User_list;

typedef struct Validation_t{
	User_list* head;
}Validation;

void addUser(Validation *valid, User *usr);
User_list* createUser_list(User *usr);
Validation* createValidation(User_list *user_list);
User* getUser(Validation *valid, char* username);
void serializeValid(Validation *valid, FILE *output);
Validation* deserializeValid(FILE *input);
void CreateAccount(char *username, char *password, char *securityAns);
logIn_state logIn(char *username, char* pass);

#endif