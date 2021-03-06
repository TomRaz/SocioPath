#ifndef User_h
#include <stdio.h>
#include <string.h>
#include "..\Common\consts.h"

#define User_h




//typedef enum { Valid, Invalid } valid_test;
typedef enum { username, password, randomNum, securityAnswer } field;

typedef struct user_t{
	char username[USERNAME_LEN + 1];
	char password[ENC_PASS_LEN + 1]; //password is saved AFTER encryption
	int randomNum;
	char securityAnswer[SECURITY_ANS_LEN + 1];

} User;

void updateUserPass(User* user, char* new_pass);
void passEncrypt(char *pass, int randomNum, char* result);
User* createUser(char *name, char* pass, char* ans);
User* createDeserializedUser(char *name, char* pass, int randomNum, char* ans);
void getUsername(User *user, char* dest);
void getPassword(User *user, char* dest);
int getrandomNum(User *user);
void getSecurityAns(User *user, char* dest);
char* SerializeUser(User *user);
User* DeserializeUser(char *str);
bool checkPassValidity(char *pass);
bool checkUserValidity(char *str);


#endif
