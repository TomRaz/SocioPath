#include "Validation.h"
#include "User.h"
#include "../Common/CommonFunctions.h"


void addUser(Validation *valid, User *usr){
	User_list* ret = createUser_list(usr);
	ret->next = valid->head;
	valid->head = ret;
	return;
}
int ValidationUserCount(Validation *valid){
	return User_list_count(valid->head);
}

void serializeValid(Validation *valid, char *PATH){
	char** items = serializeUser_list(valid->head);
	int user_num = ValidationUserCount(valid);
	/*Use common funcs to write to file*/
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

void serializeValid(Validation *valid, char *PATH){

}

void deserializeValid(Validation *valid, char *PATH){

}

void CreateAccount(Validation *valid, char *username, char *password, char *securityAns)
{
	User *usr = createUser(username, password, securityAns);
	addUser(valid, usr);
}

logIn_state logIn(Validation *valid, char *username, char* pass){
	User *usr = getUser(valid, username);
	if (usr == NULL)
		return Doesnt_Exist;
	int randomNum = getrandomNum(usr);
	char result[ENC_PASS_LEN + 1], usr_pass[ENC_PASS_LEN+1];
	getPassword(usr, usr_pass);
	passEncrypt(pass, randomNum, result);
	if (strcmp(usr_pass, result) == 0){
		return GOOD;
	}
	else
		return Wrong_Pass;
}
