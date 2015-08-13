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


Validation* createValidation(){ //Removed (User *usr)
	
	
	User_list* user_l = createUser_list();
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
	char** items = serializeUser_list(valid->head);
	int i,user_num = ValidationUserCount(valid);
	for (i = 0; i < user_num; i++){
		//writeToFile(items[i], PATH);
	}

	/*Use common funcs to write to file*/
	free2Darr(items, user_num);
}
void deserializeValid(Validation *valid, char *PATH){
	int i, lines;
	char **res = readAllLines(PATH, &lines);
	User *curr_usr;
	for (i = 0; i < lines; i++){
		curr_usr = DeserializeUser(res[i]);
		addUser(valid, curr_usr);
	}
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
		return LOGIN_GOOD;
	}
	else
		return Wrong_Pass;
}
