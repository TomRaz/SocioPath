#include "User.h"
#include "../Common/CommonFunctions.h"

typedef enum { Valid, Invalid } pass_test;

typedef struct user_t{
	char username[USERNAME_LEN + 1];
	char password[PASS_LEN+1]; //password is saved AFTER encryption
	int randomNum;
	char securityAnswer[SECURITY_ANS_LEN+1];

} User;

char* SerializeUser(User *user){
	
	int stringSize = USERNAME_LEN + PASS_LEN + SECURITY_ANS_LEN + 3 * SEP_LEN+1;
	char *ans = malloc(stringSize * sizeof(char));
	char rand_num_str[MAX_INT_LEN];
	
	
	if (ans == NULL) return NULL; //is necessary?

	strcat(ans, user->username);
	strcat(ans, SEPERATOR);
	strcat(ans, user->password);
	strcat(ans, SEPERATOR);
	itoa(user->randomNum, rand_num_str, 10);
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

pass_test checkPassValidity(char *pass){ //check password string validity BEFORE encryption
	int i;
	bool hasLower, hasUpper, hasDigit;
	
	for (i = 0; i < PASS_LEN; i++){
		if (pass[i] == '\0' || pass == NULL)
			return Invalid;
		if (isupper(pass[i]))
			hasUpper = TRUE;
		if (islower(pass[i]))
			hasLower = TRUE;
		if (isdigit(pass[i]))
			hasDigit = TRUE;
		if (!(hasDigit || hasLower || hasUpper)) //if char isn't lower, upper or a digit
			return Invalid;
	}
	if (hasDigit && hasLower && hasUpper)
		return Valid;
}