#include "User.h"

typedef struct user_t{
	char username[USERNAME_LEN + 1];
	char password[PASS_LEN+1];
	int randomNum;
	char securityAnswer[SECURITY_ANS_LEN+1];

} User;

char* SerializeUser(User *user){
	
	int stringSize = USERNAME_LEN + PASS_LEN + SECURITY_ANS_LEN + 3 * SEP_LEN+1;
	char *ans = malloc(stringSize * sizeof(char));
	char rand_num_char = user->randomNum + '0';

	if (ans == NULL) return NULL; //is necessary?

	strcat(ans, user->username);
	strcat(ans, SEPERATOR);
	strcat(ans, user->password);
	strcat(ans, SEPERATOR);
	strcat(ans, rand_num_char);
	strcat(ans, SEPERATOR);
	strcat(ans, user->securityAnswer);

	return ans;
}