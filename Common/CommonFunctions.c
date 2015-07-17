#include "CommonFunctions.h"
#include <ctype.h>


char** alloc2Darr(int rows, int cols){
	int i;
	char** res = malloc(rows*sizeof(char*));
	
	for (i = 0; i < rows; i++){
		res[i] = malloc(cols * sizeof(char));
		if (res == NULL || res[i] == NULL)
			return NULL;
	}
	return res;
}

void free2Darr(char** arr, int rows){
	int i;
	for (i = 0; i < rows; i++){
		free(arr[i]);
	}
	free(arr);
}

char** splitStr(char* str, int wordCount, int maxWordLen, char* sep_str){

	char** res = alloc2Darr(wordCount, maxWordLen);

	/* get the first token */
	char *token = strtok(res, sep_str);

	/* walk through other tokens */
	int i = 0;
	while (token != NULL)
	{
		strcpy(res[i], token);
		token = strtok(NULL, sep_str);
		i++;
	}

	return res; 
}
int isValid(char* str){//checks if all characters are letters, numbers or space
	while (*str != '\0'){
		if (isalnum(*str) == 0 && isspace(*str)==0)
			return 0;
	}
	return 1;
}

int hasDigit(char *str){ //returns the number of digits in a string
	int count = 0;
	while (*str != '\0'){
		if (isdigit(*str))
			count++;
		str++;
	}
	return count;
}
int hasLower(char *str){
	int count = 0;

	while (*str != '\0'){
		if (islower(*str))
			count++;
		str++;
	}
	return count;

}
	int hasUpper(char *str){
		int count = 0;

		while (*str != '\0'){
			if (isupper(*str))
				count++;
			str++;
		}
		return count;

	}
	int hasSpace(char *str){
		int count = 0;

		while (*str != '\0'){
			if (isspace(*str))
				count++;
			str++;
		}
		return count;

	}