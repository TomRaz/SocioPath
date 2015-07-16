#ifndef Validation_h
#define Validation_h

typedef struct User_list_t{
	User usr;
	struct User_list_t *next;

}User_list;

User_list* addUser(User_list *head, User *usr);
User_list* createUser_list(User *usr);
void serializeUser_list(User_list *head, FILE *output);
User_list* deserializeUser_list(FILE *input);

#endif