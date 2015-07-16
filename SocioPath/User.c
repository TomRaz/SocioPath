#include "User.h"
#include "../Common/CommonFunctions.h"



void passEncrypt(char* pass, int randomNum, char* result){
	int ans = pass[0];
	int i;

	for (i = 1; i < PASS_LEN; i++){
		ans = ans & pass[i];
	}
	if (ans % 2 == 0)
		ans = ans << 4;
	else
		ans = ans >> 6;
	ans = ans^randomNum;
	itoa(ans, result, 2);
}

User* newUser(char *name, char* pass, char* ans){

	srand(time(NULL));
	int randomNum = rand(), passInt;
	char encryptedPass[ENC_PASS_LEN + 1];
	User* user = malloc(sizeof(User));
	if (user == NULL)
		return NULL;

	passEncrypt(pass, randomNum, encryptedPass);

	strcpy(user->username, name);
	strcpy(user->password, encryptedPass);
	user->randomNum = randomNum;
	strcpy(user->securityAnswer, ans);

	return user;

}


char* SerializeUser(User *user){
	
	int stringSize = USERNAME_LEN + ENC_PASS_LEN + SECURITY_ANS_LEN + 3 * SEP_LEN+1;
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

User* DeserializeUser(char *str){
	
	char** res = splitStr(str, USR_WRD_CNT, SECURITY_ANS_LEN, SEPERATOR);
	if (str == NULL || res == NULL) return NULL; //is necessary?

	User *user = newUser(res[0], res[1], atoi(res[2]), res[3]); 

	free2Darr(res, 4);

	return user;
}

valid_test checkValidity(char *str, field fld ){ //fld = username OR password (before encryption)
	int i, len;
	bool hasLower = FALSE, hasUpper = FALSE, hasDigit = FALSE, hasSpace = FALSE;
	
	if (str == NULL)
		return Invalid;

	if (fld == username)
		len = USERNAME_LEN;
	if (fld == password)
		len = PASS_LEN;
	else
		len = 0; //error

	for (i = 0; i < len; i++){
		
		if (str[i] == '\0')
			break;
		if (isalnum(str[i]) || str[i]== ' '){
			
			if (isupper(str[i]))
				hasUpper = TRUE;
			if (islower(str[i]))
				hasLower = TRUE;
			if (isdigit(str[i]))
				hasDigit = TRUE;
			if (str[i] == ' ')
				hasSpace = TRUE;
		}
		else
			return Invalid;
	}
	if (fld == password){
		if (hasDigit && hasLower && hasUpper && (hasSpace == FALSE) && i == len) //length is 8 and contains lower, upper and a digit
			return Valid;
		else
			return Invalid;
	}
	if (fld == username && i > 0)
		return Valid;
	
	return Invalid;
	}

