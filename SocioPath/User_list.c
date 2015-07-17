#include "User.h"
#include "Validation.h"
#include "User_list.h"
#include "../Common/CommonFunctions.h"
#include "../Common/consts.h"


User_list* createUser_list(User *usr){
	User_list *ans = malloc(sizeof(User_list));
	ans->usr = *usr;
	return ans;
}

int User_list_count(User_list* user_list){
	int count = 0;
	while (user_list->next != NULL)
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
	for (i = 0; i < item_num; i++){
		strcpy(result[i], SerializeUser(&curr->usr));
		curr = curr->next;
	}
	return result;
}