#ifndef User_h
#include <stdio.h>
#include <string.h>

#define User_h


typedef enum { Valid, Invalid } valid_test;
typedef enum { username, password, randomNum, securityAnswer } field;


#define USR_WRD_CNT 3
#define USERNAME_LEN 50
#define PASS_LEN 8
#define ENC_PASS_LEN 32
#define SECURITY_ANS_LEN 100
#define SEPERATOR "_$_"
#define SEP_LEN 3
#define MAX_INT_LEN 8

passEncrypt(char *pass, int randomNum);
User* newUser(char *name, char* pass, char* ans);
char* SerializeUser(User *user);
User* DeserializeUser(char *str);
valid_test checkValidity(char *str, field fld);


#endif
