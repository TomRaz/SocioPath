#include "User.h"
#include "../Common/CommonFunctions.h"

typedef struct user_t{
	char username[USERNAME_LEN + 1];
	char password[PASS_LEN+1];
	int randomNum;
	char securityAnswer[SECURITY_ANS_LEN+1];

} User;

char* SerializeUser(User *user){
	
	int stringSize = USERNAME_LEN + PASS_LEN + SECURITY_ANS_LEN + 3 * SEP_LEN+1;
	char *ans = malloc(stringSize * sizeof(char));
	char rand_num_str[MAX_INT_LEN] = itoa(user->randomNum);
	
	if (ans == NULL) return NULL; //is necessary?

	strcat(ans, user->username);
	strcat(ans, SEPERATOR);
	strcat(ans, user->password);
	strcat(ans, SEPERATOR);
	strcat(ans, rand_num_str);
	strcat(ans, SEPERATOR);
	strcat(ans, user->securityAnswer);

	return ans;
}

User* DesrializeUser(char *str){
	
	User *user = malloc(sizeof(User));
	
	if (str == NULL || user == NULL) return NULL; //is necessary?
	char** res = splitStr(str, USR_WRD_CNT, SECURITY_ANS_LEN, SEPERATOR);

	strcpy(user->username, res[0]);
	strcpy(user->password, res[1]);
	strcpy(user->randomNum, atoi(res[2])); //string to int for randomNum
	strcpy(user->securityAnswer, res[3]);

	free2Darr(res, 4);

	return user;
}