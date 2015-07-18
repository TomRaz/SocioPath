#ifndef CheckRequestsDialog_h
#define CheckRequestsDialog_h

#include "Profile.h"
#include "ProfilesManager.h"



Profile** getUserFromProfileList(Profile** profiles, int listLen, char* name);

Profile* parseAcceptOrReject(char* cmd, Profile** profiles, int numOfFriends);
void checkRequestsDialog(ProfileManager* manager, Profile* curProfile);
Profile** fetchAndPrintFriendRequests(ProfileManager* manager, Profile* curProfile, int* numberOfFriends);
void askForUserAction(Profile** profiles, Profile* curProfile, int numOfFriends);

#endif