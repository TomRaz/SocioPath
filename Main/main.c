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

void startUI(){
    ProfileUI* ui = newProfileUI("amir");
    startProfileUI(ui);
    saveData(ui);
}

int main(){
	
	bool a;

	char sec[SECURITY_ANS_LEN];
	Validation *valid = createValidation();
	deserializeValid(valid, VALIDATION_PATH);
	int count = ValidationUserCount(valid);
	
	//printf("\n%d\n", count);
	/*char pass1[PASS_LEN + 1], pass2[PASS_LEN + 1], result1[ENC_PASS_LEN + 1], result2[ENC_PASS_LEN + 1];
	int num = 12345;
	strcpy(pass1, "abcdA123");
	strcpy(pass2, "abccA123");
	passEncrypt(pass1, num, result1);
	passEncrypt(pass2, num, result2);
	printf("\n%s", result1);
	printf("\n%s", result2);*/
	
	
	MainLoginDialog(valid);
	//startUI();
    //testProfileManager();
}