#include "Validation.h"
#include "User.h"
#include "../Common/CommonFunctions.h"


void addUser(Validation *valid, User *usr){
	User_list* ret = createUser_list(usr);
	ret->next = valid->head;
	valid->head = ret;
	return;
}

User_list* createUser_list(User *usr){
	User_list *ans = malloc(sizeof(User_list));
	ans->usr = *usr;
	return ans;
}

Validation* createValidation(User *usr){
	
	User_list* user_l = createUser_list(usr);
	Validation* valid = malloc(sizeof(Validation));
	valid->head = user_l;
	return valid;
}

User* getUser(Validation* valid, char* username){ 

	char curr_username[USERNAME_LEN + 1];
	User_list* lst = valid->head;
	while (lst != NULL){
		getUsername(lst, curr_username);
		if (strcmp(curr_username, username) == 0)
			return &lst->usr;
		lst = lst->next;
	}
			return NULL;
	}

void serializeValid(Validation *valid, FILE *output){

}

Validation* deserializeValid(FILE *input){

}

void CreateAccount(char *username, char *password, char *securityAns)
{
	User usr* = crea
}

logIn_state logIn(char *username, char* pass){

}
