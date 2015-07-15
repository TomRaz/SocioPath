#include "User.h"
#include "../Common/CommonFunctions.h"


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

valid_test checkValidity(char *str, field fld ){ //check string validity for password BEFORE encryption or username
	int i, len;
	bool hasLower = FALSE, hasUpper = FALSE, hasDigit = FALSE, hasSpace = FALSE;
	
	if (str == NULL)
		return Invalid;

	switch (fld)
	{
	case username:	{
		len = USERNAME_LEN;
		break;
	}
	case password: {
		len = PASS_LEN;
		break;
	}
	default: len = 0;
	}
	

	for (i = 0; i < len; i++){
		
		if (str[i] == '\0')
			break;
		if (isalnum(str[i]) || isspace(str[i])){
			
			if (isupper(str[i]))
				hasUpper = TRUE;
			if (islower(str[i]))
				hasLower = TRUE;
			if (isdigit(str[i]))
				hasDigit = TRUE;
			if (isspace(str[i]))
				hasSpace = TRUE;
		}
		else
			return Invalid;
	}
	switch (fld){
	case username:
	{
		return Valid;
		break;
	}
	case password:
	{
		if (hasDigit && hasLower && hasUpper && (hasSpace == FALSE) && i == len) //length is 8 and contains lower, upper and a digit
			return Valid;
		else
			return Invalid;
		break;
	}
	return Invalid;
	}
}
