#include "../Common/CommonFunctions.h"
#include "../Profiles/Profile.h"
#include "../Profiles/ProfilesManager.h"
#include "../Profiles/ProfileUI.h"
#include "../SocioPath/ValidationUI.h"
#include "../SocioPath/Validation.h"
#include "../Common/consts.h"

void testProfileManager(){
    ProfileManager *p = deserializeProfileManager("c:\\temp\\profiles.txt");
    FriendRef* f = p->head->profile->friendsHead->next;
    FriendRef* f2 = f->next;
    serializeProfileManager(p, "c:\\temp\\priflesNew.txt");
    freeProfileManager(p);
}


int main(){
	
	bool a;

	char sec[SECURITY_ANS_LEN];
	Validation *valid = createValidation();
	deserializeValid(valid, VALIDATION_PATH);
	int count = ValidationUserCount(valid);
	MainLoginDialog(valid);
}