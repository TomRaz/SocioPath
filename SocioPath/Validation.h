#ifndef Validation_h
#define Validation_h

typedef enum {Wrong_Pass, Doesnt_Exist, GOOD} logIn_state;

typedef struct User_list_t{
	User usr;
	struct User_list_t *next;

}User_list;

User_list* addUser(User_list *head, User *usr);
User_list* createUser_list(User *usr);
User* getUser(User_list* head, char* username);
void serializeUser_list(User_list *head, FILE *output);
User_list* deserializeUser_list(FILE *input);
void CreateAccount(char *username, char *password, char *securityAns);
logIn_state logIn(char *username, char* pass);

#endif