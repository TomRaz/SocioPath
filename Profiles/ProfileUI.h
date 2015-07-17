#ifndef ProfileUI_h
#define ProfileUI_h

#include "Profile.h"
#include "ProfilesManager.h"

typedef struct profile_ui_t{
    Profile* curProfile;
    ProfileManager* profileManager;
} ProfileUI;

ProfileUI* newProfileUI(char* username);
void startProfileUI(ProfileUI* ui);
void saveData(ProfileUI* ui);
void mainDialog(ProfileUI* ui);
void printOptions();
char* extractUsernameFromCmd(char* cmd);

#endif