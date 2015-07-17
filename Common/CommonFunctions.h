#ifndef CommonFunctions_h
#define CommonFunctions_h
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef enum { TRUE, FALSE } bool;


char** alloc2Darr(int rows, int cols);
void free2Darr(char** arr, int rows);

char** splitStr(char* str, int wordCount, int maxWordLen, char* sep_str);
char** splitStr2(char* a_str, char *a_delim, int *splittedSize);

void setArrVal(char *arr, int size, char val);
int hasDigit(char *str); //returns the number of digits in a string
int hasLower(char *str);
int hasUpper(char *str);
int hasSpace(char *str);

char** readAllLines(char* path, int *lines);


#define SOCIO_ASSERT(exp, msg) if(!exp){ printf("%s\n", msg); assert(0);}

#define SOCIO_ASSERT_MEM(exp) SOCIO_ASSERT(exp, "Memory allocation failed")

#endif


