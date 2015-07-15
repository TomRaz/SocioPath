#include "CommonFunctions.h"


void test(){
    printf("hey");
}

char** alloc2Darr(int rows, int cols){
	int i;
	char** res = malloc(rows*sizeof(char*));
	
	for (i = 0; i < rows; i++){
		res[i] = malloc(cols * sizeof(char));
		if (res == NULL || res[i] == NULL)
			reurn NULL;
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
