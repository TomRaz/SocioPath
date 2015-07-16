#include "Validation.h"
#include "User.h"
#include "../Common/CommonFunctions.h"


User_list* addUser(User_list *head, User *usr){
	User_list* ret = createUser_list(usr);
	ret->next = head;
	return ret;
}

User_list* createUser_list(User *usr){
	User_list *ans = malloc(sizeof(User_list));
	ans->usr = *usr;
	return ans;
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



void serializeUser_list(User_list *head, FILE *output){

}

User_list* deserializeUser_list(FILE *input){

}

void CreateAccount(char *username, char *password, char *securityAns)
{

}

logIn_state logIn(char *username, char* pass){

}
