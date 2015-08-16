#include "CommonFunctions.h"
#include <ctype.h>
#include "consts.h"
#include <stdio.h>


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
	char *token = strtok(str, sep_str);

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

char** splitStr2(char* a_str, char *a_delim, int *splittedSize)
{
    char *ch;
    char** res = malloc(sizeof(char*));
    int count = 0;
    ch = strtok(a_str, a_delim);
    while (ch != NULL) {
        res = realloc(res, (count + 1)*sizeof(char*));
        res[count] = malloc(sizeof(char)*strlen(ch)+1);        
        strcpy(res[count], ch);
        ch = strtok(NULL, a_delim);
        count++;
    }
    *splittedSize = count;
    return res;

}
int isValid(char* str){//checks if all characters are letters, numbers or space
	char* tmp = str;
	while (*tmp != '\0'){
		if (isalnum(*tmp) == 0 && isspace(*tmp)==0)
			return 0;
		tmp++;
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

void setArrVal(char *arr, int size, char val){
		int i;
		for (i = 0; i < size; i++){
			arr[i] = val;
		}
}


char** readAllLines(char* path, int *lines){
    FILE* fh;
    fopen_s(&fh, path, "r");

    char** res = (char**)malloc(1);
    if (res == NULL)
        return NULL;

    //check if file exists
    if (fh == NULL){
        printf("file does not exists %s\n", path);
        return 0;
    }


    //read line by line
    char line[MAX_LINE_SIZE];
    *lines = 0;
    while (fgets(line, MAX_LINE_SIZE, fh) != NULL){
        res = (char**)realloc(res, (*lines + 1)*sizeof(char**));
        if (!res){
            for (int j = 0; j < *lines; j++)
                free(res[j]);
            free(res);
            return NULL;
        }
        int lineLength = strlen(line);
        res[*lines] = malloc(sizeof(char)*lineLength);
        strncpy(res[*lines], line, lineLength-1); //copy without the /n
        res[*lines][lineLength - 1] = '\0';
        (*lines)++;
    }

    fclose(fh);
    return res;
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

//http://www.dateiliste.com/en/source-code/16-cc/577-stristr-case-insensitive-strstr-function.html
char *stristr(char *ch1, char *ch2)
{
    char  *chN1, *chN2;
    char  *chNdx;
    char  *chRet = NULL;

    chN1 = strdup(ch1);
    chN2 = strdup(ch2);
    if (chN1 && chN2)
    {
        chNdx = chN1;
        while (*chNdx)
        {
            *chNdx = (char)tolower(*chNdx);
            chNdx++;
        }
        chNdx = chN2;
        while (*chNdx)
        {
            *chNdx = (char)tolower(*chNdx);
            chNdx++;
        }
        chNdx = strstr(chN1, chN2);
        if (chNdx)
            chRet = ch1 + (chNdx - chN1);
    }
    free(chN1);
    free(chN2);
    return chRet;
}
