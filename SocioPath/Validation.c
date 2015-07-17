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

User* getUser(User_list* head, char* username){ 

	char tmp[USERNAME_LEN + 1];

	while (head != NULL){
		getUsername(&head->usr, tmp);
		if (strcmp(tmp, username) == 0)
			return &head->usr;
		head = head->next;
	}
		if (head == NULL)
			return NULL;
	}

void serializeValid(Validation *valid, FILE *output){

}

Validation* deserializeValid(FILE *input){

}

void CreateAccount(char *username, char *password, char *securityAns)
{
	
}

logIn_state logIn(char *username, char* pass){

}
