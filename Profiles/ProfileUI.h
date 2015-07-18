#ifndef ProfileUI_h
#define ProfileUI_h

#include "Profile.h"
#include "ProfilesManager.h"

typedef struct profile_ui_t{
    Profile* curProfile;
    ProfileManager* profileManager;
} ProfileUI;

ProfileUI* newProfileUI(char* username);
//use the return value to decide if to exit or if to log in with another user
bool startProfileUI(ProfileUI* ui);
void saveData(ProfileUI* ui);
bool mainDialog(ProfileUI* ui);
void printOptions();
char* extractUsernameFromCmd(char* cmd);
void showProfile(ProfileUI* ui, char* friendsStatusHeader);
void printFriends(ProfileUI* ui);
void searchProfile(ProfileUI* ui, char* name);
void checkFriendStatus(ProfileUI* ui, char* name);
void unfriend(ProfileUI* ui, char* name);
void updateStatusDialog(ProfileUI* ui);
void sendFriendRequest(ProfileUI* ui, char* name);
void printNetwork(ProfileUI* ui);

#endif