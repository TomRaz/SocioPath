#ifndef User_list_h
#define User_list_h

typedef struct User_list_item{
	User *usr;
	struct User_list_item *next;

}User_list;

User_list* createUser_list();
User_list* AddUserToList(User_list* head, char* username, char* password, char* securityAnswer);
char** serializeUser_list(User_list *user_list);
int User_list_count(User_list* user_list);


#endif