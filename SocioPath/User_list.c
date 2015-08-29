	#include "User.h"
	#include "Validation.h"
	#include "User_list.h"
	#include "../Common/CommonFunctions.h"
	#include "../Common/consts.h"


User_list* createUser_list(User *usr){
	User_list *ans = malloc(sizeof(User_list));
	ans->usr = usr;
	ans->next = NULL;
	
	return ans;
}
User_list* AddUserToList(User_list* head, char* username, char* password, char* securityAnswer){
	User* Newuser = createUser(username, password, securityAnswer);
	if (head->usr == NULL){
		head->usr = Newuser;
	}
	else{

	User_list* new_item = createUser_list(Newuser);
	new_item->next = head->next;
	head->next = new_item;
}
	return head;
}


int User_list_count(User_list* user_list){
	int count = 0;

	while (user_list != NULL && user_list->usr != NULL)
	{
		count++;
		user_list = user_list->next;

	}
	return count;
}

char** serializeUser_list(User_list *user_list){
	int max_usr_str_len = USERNAME_LEN + PASS_LEN + MAX_INT_LEN + SECURITY_ANS_LEN + 3 * SEP_LEN;
	int i,item_num = User_list_count(user_list);
	User_list* curr = user_list;
	char **result = alloc2Darr(item_num, max_usr_str_len);
	for (i = 0; i < item_num && curr->usr != NULL; i++){
		strcpy(result[i], SerializeUser(curr->usr));
		curr = curr->next;
	}
	return result;
}