#ifndef Profile_h
#define Profile_h

#include "..\Common\consts.h"

typedef struct friend_ref_item{
    char data[USERNAME_LEN];
    struct string_item_t* next;
} FriendRef;

typedef struct profile_t{
    char username[USERNAME_LEN + 1];
    char status[STATUS_MAX_SIZE + 1]; 
    FriendRef* friendsHead;
    int friendsCount;
    FriendRef* pendingRequestsHead;
    int pendingRequestsCount;

} Profile;

Profile* deserializeProfile(char** lines);
char* serializeProfile(Profile* profile);
void freeProfile(Profile* p);
void addFriend(Profile* profile, char* friendName);
void addPendingRequest(Profile* profile, char* friendName);
Profile* newProfile(char* name);


typedef struct profile_list_t{
    Profile* profile;
    struct Profile *next;
}ProfileListItem;

ProfileListItem* add(ProfileListItem* list, Profile* item);





#endif