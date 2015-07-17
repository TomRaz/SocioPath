#include "User.h"
#include "Validation.h"
#include "../Common/CommonFunctions.h"
#include "../Common/consts.h"


User_list* createUser_list(User *usr){
	User_list *ans = malloc(sizeof(User_list));
	ans->usr = *usr;
	return ans;
}
char** serializeUser_list(User_list *user_list){

	SerializeUser(&user_list->usr);
}