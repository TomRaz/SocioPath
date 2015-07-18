#include "../Common/CommonFunctions.h"
#include "../Profiles/Profile.h"
#include "../Profiles/ProfilesManager.h"
#include "../Profiles/ProfileUI.h"

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

//test 1243
int main(){
    startUI();
    //testProfileManager();
}