#ifndef ProfileManager_h
#define ProfileManager_h

#include "Profile.h"


typedef struct profileManager_t{    
    ProfileListItem* head;
    int profilesCount;
} ProfileManager;

ProfileManager* deserializeProfileManager(char* path);
void serializeProfileManager(ProfileManager* manager, char* path);
void freeProfileManager(ProfileManager* manager);
void addProfile(ProfileManager* manager, Profile* profile);
Profile* getProfile(ProfileManager* manager, char* name);
Profile* createProfile(ProfileManager* manager, char* name);
char* getFriendsStatuses(ProfileManager* manager, Profile* profile);
Profile** getUsersFriends(ProfileManager* manager, Profile* profile, int* numOfFriends);

char* getFriendsStatus(ProfileManager* manager, char* friendName);

#endif