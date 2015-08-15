#ifndef ValidationUI_h
#define ValidationUI_h
#include "User.h"
#include "User_list.h"
#include "Validation.h"

typedef enum { USER_GOOD, EXISTS, NOT_VALID } Username_test;
typedef enum {GOOD, BAD, RECOVER, MAIN_SCREEN, EXIT_APP} Pass_menu;

void printWelcome();
void printToggle();
int startValidationUI();
bool MainLoginDialog(Validation *valid);
logIn_state LoginUI(Validation *valid);
bool newUserUI(Validation *valid);
bool getNewSecurityAns(char *ans);
bool getNewPass(char* password);
Pass_menu getPass(char* password);
Pass_menu recoverPass(Validation *valid,char* user);
Username_test getNewUsername(Validation *valid, char* username);
bool getLoginString(char *username, char *password);
logIn_state handleWrongPass(Validation *valid, char* username);


#endif