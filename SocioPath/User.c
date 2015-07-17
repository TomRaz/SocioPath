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

void getUsername(User *user, char* dest)
{
	if (user == NULL || dest == NULL)
		return;
	strcpy(dest, user->username);
}
void getPassword(User *user, char* dest){
	if (user == NULL || dest == NULL)
		return;
	strcpy(dest, user->password);
}

int getrandomNum(User *user){
	if (user == NULL)
		return -1; //error
	return user->randomNum;
}

void getSecurityAns(User *user, char* dest){
	if (user == NULL || dest == NULL)
		return;
	strcpy(dest, user->securityAnswer);
}


User* createUser(char *name, char* pass, char* ans){

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
    if (str == NULL || res == NULL){
        return NULL; //is necessary?
    }
	User *user = newUser(res[0], res[1], atoi(res[2]), res[3]); 

	free2Darr(res, 4);

	return user;
}



valid_test checkUserValidity(char *str){
	int len = strlen(str), sum = 0;
	if (isValid(str) == 0)
		return Invalid;
	sum = hasLower(str) + hasUpper(str) + hasSpace(str);
	if (len == sum)
		return Valid;
	return Invalid;
	}

valid_test checkPassValidity(char *pass){ 
	int len = strlen(pass);
	if (isValid(pass) == 0)
		return Invalid;
	if (len == 8 && hasDigit(pass) && hasLower(pass) && hasUpper(pass) && hasSpace(pass)==0)
		return Valid;
	return Invalid;
}