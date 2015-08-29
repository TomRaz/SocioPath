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
bool removeFriend(Profile* profile, char* name);
bool isFriend(Profile* profile, char* name);
bool isFriendRequestPending(Profile* profile, char* name);
bool removePendingFriendRequest(Profile* profile, char* name);
bool acceptFriendRequest(Profile* mine, Profile* other);
bool rejectFriendRequest(Profile* mine, Profile* other);



typedef struct profile_list_t{
    Profile* profile;
    struct Profile *next;
}ProfileListItem;

ProfileListItem* addProfileItem(ProfileListItem* list, Profile* item);





#endif