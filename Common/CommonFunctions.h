#ifndef CommonFunctions_h
#define CommonFunctions_h
#include <string.h>

void test();

char** alloc2Darr(int rows, int cols);
char** free2Darr(char** arr, int rows);

char** splitStr(char* str, int wordCount, int maxWordLen, char* sep_str);

#endif