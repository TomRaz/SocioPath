#ifndef User_h
#include <stdio.h>
#include <string.h>

#define User_h

#define USR_WRD_CNT 3
#define USERNAME_LEN 50
#define PASS_LEN 8
#define SECURITY_ANS_LEN 100
#define SEPERATOR "_$_"
#define SEP_LEN 3
#define MAX_INT_LEN 8

char* SerializeUser(User *user);
User* DesrializeUser(char *str);
pass_test checkPassValidity(char *pass);


#endif
