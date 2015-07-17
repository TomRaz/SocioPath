#include "CommonFunctions.h"
#include <stdio.h>
#include "consts.h"


char** alloc2Darr(int rows, int cols){
	int i;
	char** res = malloc(rows*sizeof(char*));
	
	for (i = 0; i < rows; i++){
		res[i] = malloc(cols * sizeof(char));
		if (res == NULL || res[i] == NULL)
			return NULL;
	}
}

char** free2Darr(char** arr, int rows){
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

char** readAllLines(char* path, int *lines){
    FILE* fh;
    fopen_s(&fh, path, "r");

    char** res = (char**)malloc(1);
    if (res == NULL)
        return NULL;

    //check if file exists
    if (fh == NULL){
        printf("file does not exists %s", path);
        return 0;
    }


    //read line by line
    char line[MAX_LINE_SIZE];
    *lines = 0;
    while (fgets(line, MAX_LINE_SIZE, fh) != NULL){
        int b = (*lines + 1)*sizeof(char)*MAX_LINE_SIZE;
        res = (char**)realloc(res, (*lines+1)*sizeof(char**));
        if (!res){
            for (int j = 0; j < *lines; j++)
                free(res[j]);
            free(res);
            return NULL;
        }            
        res[*lines] = malloc(sizeof(char)*strlen(line));
        strcpy(res[*lines], line);
        (*lines)++;
    }
    return res;
}
