
#include "../Common/CommonFunctions.h"
#include "../Common/consts.h"
#include "../Profiles/ProfileUI.h"
#include "ValidationUI.h"

void printWelcome(){
	printf("Hello dear guest and welcome to 'SocioPath - Socialize in an alternative path!'\n");
}

void printToggle(){
	printf("To go back the first screen enter '#'\n");
	printf("To exit the app please enter '$'\n");
}

int startValidationUI(){
	int choice;
	printWelcome();
	do{
		printf("What would you like to do next? \n");
		printf("1. Log in \n2.Create a new account \n3.Exit the app\n\n");
		printf("Input:");
		scanf("%d", &choice);
		if (choice < 1 || choice > 3)
			printf("Please select a valid option\n");
	} while (choice < 1 || choice > 3);
	return choice;
}

bool MainLoginDialog(Validation *valid){
	int mode;
	logIn_state state;
	
	mode = startValidationUI();
	printf("%s", UI_SEPERATOR);
	switch (mode){
	case 1: //Login
	{
		state = LoginUI(valid);
		break;
	}
	case 2: //Create new user
	{
		newUserUI(valid);
		break;
	}
	case 3:
	{
		return FALSE; //exit app
	}
	}
	return TRUE;
	
}
int getStringAsAsterik(char *str){
	char c;
	int i = 0;
	while ((c = getch()) != 13) {
		str[i] = c;
		printf("*");
		i++;
	}
	printf("\n");
	return i;
}

bool getLoginString(char *username, char *password){
	char user_str[USERNAME_LEN + 1] = { 0 }, pass_str[PASS_LEN + 1] = { 0 };
	int i=0;
	bool pass_flag = FALSE;
	char c,d ;
	c = getch();
	/*if (c == '$' || c == '#')
	{
		username[0] = c;
		return FALSE;
	}*/
	while (c != 13){
		printf("%c", c);
		if (c == ':' && pass_flag == FALSE)
			if (d = getch() == ':'){
				printf(":");
			pass_flag = TRUE;
			i = 0;
		}
			else{
				return FALSE;
			}
		if (pass_flag == FALSE){
			user_str[i] = c;
			c = getch();
			i++;
		}
		else{
			i = getStringAsAsterik(pass_str);
			if (checkPassValidity(pass_str) == FALSE){
				strcpy(username, user_str);
				strcpy(password, pass_str);
				return FALSE;
			}
			break;
		}
	}
	printf("\n");
	
	strcpy(username, user_str);
	strcpy(password, pass_str);
	if (pass_flag == FALSE)
		return FALSE;
	return TRUE;

}

Pass_menu getPass(char* password)
		{
			char tmp[PASS_LEN+1] = { 0 };
			int len = 0;

			do {
				printf("Enter password: ");
				len = getStringAsAsterik(tmp);
				if (tmp[0] == '!')
					return RECOVER;
				if (tmp[0] == '$')
					return EXIT_APP;
				if (tmp[0] == '#')
					return MAIN_SCREEN;
				if (len < 8)
					printf("password not long enough.\n");
			} while (len !=8);
			if (isValid(tmp)==1){
				strncpy(password, tmp,9);
				return GOOD;
		}
}

bool getNewPass(char* password, char* username){
	char pass1[PASS_LEN+1], pass2[PASS_LEN+1];
	bool pass1_test, pass2_test;
	printf("Hello %s, Please enter your new password:\n", username);

	pass1_test = getPass(pass1);
	printf("Please enter password again for confirmation:\n");
	pass2_test = getPass(pass2);
	if (pass1_test == TRUE && pass2_test == TRUE)
	{
		if (strcmp(pass1, pass2) == 0)
		{
			strncpy(password, pass1, 9);
			return TRUE;
		}
		else
			printf("The two passwords doesn't match, please try again.\n\n");
	}
	return FALSE;

}

bool getNewSecurityAns(char *ans){
	char tmp[SECURITY_ANS_LEN+1];
	printf("Question: Where did you perform your last air guitar jam?\n Answer: ");
	fflush(stdin);
	fgets(tmp, SECURITY_ANS_LEN, stdin);
	strtok(tmp, "\n");
	if (isValid(tmp) == 1){
		strcpy(ans, tmp);
		return TRUE;
	}
	else return FALSE;
}

bool newUserUI(Validation *valid)
{
	char username[USERNAME_LEN+1], password[PASS_LEN+1], securityAnswer[SECURITY_ANS_LEN+1];
	Username_test usr_tst;
	bool good_pass, secAns;
	
	usr_tst = getNewUsername(valid, username);

	do {
		good_pass = getNewPass(password, username);

	} while (good_pass != TRUE);

	do{
		secAns = getNewSecurityAns(securityAnswer);
	} while (secAns != TRUE);

	CreateAccount(valid, username, password, securityAnswer);

	//ProfileUI *ui = newProfileUI(username); //TODO: Merge with Profile section
	//startProfileUI(ui);
}

void wrongPassMenu()
{
	printf("\nWrong password was entered. Please Try again\n");
	printf("To recover lost password, please enter '!'\n");
	printToggle();
}

logIn_state LoginUI(Validation *valid)
{

	char cmd[MAX_LOGIN_CMD_SIZE];
	char **splitted = alloc2Darr(2, USERNAME_LEN);
	char user[USERNAME_LEN + 1], pass[PASS_LEN + 1];
	logIn_state ans = LOGIN_GOOD;
	bool login_str;
	do{

		fflush(stdin);
		do{
			printf("Please enter your username and password in the format 'username::password'.\n ");
			printToggle();
			printf("\nInput:");
			login_str = getLoginString(user, pass);
			if (user[0] == '$')
				exit(0);
			if (user[0] == '#')
				return MainLoginDialog(valid);
			if (login_str == FALSE){
				if (getUser(valid, user) == NULL){
					printf("Username doesn't Exist, please try again\n");
					printf("Please enter your username and password in the format 'username::password'.\n ");
				}
				else{
					handleWrongPass(valid, user);

				}
			}
		} while (login_str != TRUE);
		//remove trailing newline
		strtok(cmd, "\n");
		if (strlen(user) > USERNAME_LEN || strlen(pass) != 8){
			ans = BAD_FRMT;
		}
		if (ans == LOGIN_GOOD){
			 ans = logIn(valid, user, pass);
		}
		switch (ans)
		{
		case LOGIN_GOOD:
		{
			printf("Login success\n");
			break;
		}
		case Wrong_Pass:
		{
			handleWrongPass(valid, user);
		}
		case Doesnt_Exist:{
			printf("Username doesn't exist\n");
			break;
		}
		case BAD_FRMT:{
			printf("Wrong input, please try again\n");
			break;
		}
		}
	} while (ans != LOGIN_GOOD && ans != EXIT);
	return ans;
}

logIn_state handleWrongPass(Validation *valid, char* username){
	logIn_state ans = LOGIN_GOOD;
	char pass[PASS_LEN + 1];
	Pass_menu pass_menu1, recover1;
	wrongPassMenu();
	pass_menu1 = getPass(pass);
	switch (pass_menu1){
	case GOOD:
	{
		ans = LOGIN_GOOD;
		break;
	}
	case BAD:
	{
		ans = Wrong_Pass;
		break;
	}
	case RECOVER:
	{
		recover1 = recoverPass(valid, username);
		break;
	}
	case MAIN_SCREEN:
	{

		break;
	}
	case EXIT_APP:
	{

		break;
	}
	}
	return ans;
}

Username_test getNewUsername(Validation *valid, char* username){
	char tmp_username[USERNAME_LEN];
	int i = 1;
	User *test;
	Username_test ret;

	printf("Hello dear guest, please select a username.\n");
	printToggle();
	do{
	printf("Input: ");
	fflush(stdin);
	fgets(tmp_username, sizeof(tmp_username), stdin);
	printf("%s", tmp_username);
	if (tmp_username[0] == '$')
		exit(0);
	if (tmp_username[0] == '#')
	{
		MainLoginDialog(valid);
		exit(0);
	}
	strtok(tmp_username, "\n");

	test = getUser(valid, tmp_username);
	if (test != NULL){
		printf("username taken, please try again.\n");
		ret= EXISTS;
	}
	if (checkUserValidity(tmp_username) == TRUE)
	{
		strcpy(username, tmp_username);
		ret= USER_GOOD;
	}
	else {
		printf("Username is Invalid, please try again.\n");
		ret= NOT_VALID;
	}
	} while (ret != USER_GOOD);
	return ret;
	}

Pass_menu recoverPass(Validation *valid, char* username){
	char good_answer[SECURITY_ANS_LEN + 1], tmp_answer[SECURITY_ANS_LEN + 1], new_pass[PASS_LEN + 1];
	User* user = getUser(valid, username);
	getSecurityAns(user, good_answer); //From database
	
	getNewSecurityAns(tmp_answer); //new user input
	if (tmp_answer[0] == '#')
		return MAIN_SCREEN;
	if (tmp_answer[0] == '$')
		return EXIT_APP;
	if (strcmp(good_answer, tmp_answer) == 0)
	{
		printf("%s, your answer is correct. Please select a new password.\n", username);
		getNewPass(new_pass, username);
		updatePass(valid, username, new_pass);
		printf("Password updated.\n");
		return GOOD;
	}
	

}