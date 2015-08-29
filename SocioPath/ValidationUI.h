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
Pass_menu getPass(Validation *valid, char* password);
Pass_menu recoverPass(Validation *valid,char* user);
bool getNewPass(Validation *valid, char* password, char* username);
bool getLoginString(char *username, char *password);
logIn_state handleWrongPass(Validation *valid, char* username);
void exit_app(Validation *valid);
Username_test getNewUsername(Validation *valid, char* username);
int getStringAsAsterik(char *str);

void wrongPassMenu();

#endif