#include "Profile.h"
#include "../Common/CommonFunctions.h"
#include <stdio.h>
#include <assert.h>

#define USER_NAME_PREFIX_LEN 9
#define STATUS_PREFIX_LEN 7
#define FRIEND_PREFIX_LENGTH 8
#define PENDING_REQ_PREFIX_LENGTH 8

Profile* deserializeProfile(char** lines){
    Profile *p = (Profile*)malloc(sizeof(Profile));
    SOCIO_ASSERT(p,"Error allocating memory, exiting");
    p->pendingRequestsHead = NULL;
    p->friendsHead = NULL;
    p->friendsCount = 0;
    p->pendingRequestsCount = 0;

    strcpy(p->username, lines[0] + USER_NAME_PREFIX_LEN);
    strcpy(p->status, lines[1] + STATUS_PREFIX_LEN);

    int splittedStrings;
    char** res = splitStr2(lines[2] + FRIEND_PREFIX_LENGTH, LIST_SEPERATOR, &splittedStrings);
    for (int i = 0; i < splittedStrings;i++){
        addFriend(p, res[i]);
    }
    free2Darr(res, splittedStrings);
    res = splitStr2(lines[3] + PENDING_REQ_PREFIX_LENGTH, LIST_SEPERATOR, &splittedStrings);
    for (int i = 0; i < splittedStrings; i++){
        addPendingRequest(p, res[i]);
    }
    free2Darr(res, splittedStrings);
    return p;
}

void freeFriendRefList(FriendRef* list){
    while (list != NULL){
        FriendRef* next = list->next;
        free(list);
        list = next;
    }
}
void freeProfile(Profile* p){
    freeFriendRefList(p->friendsHead);
    freeFriendRefList(p->pendingRequestsHead);
    free(p);
}

void addToFriendRefList(FriendRef** list, char* friendName){
    FriendRef* friendRef = (FriendRef*)malloc(sizeof(FriendRef));
    SOCIO_ASSERT(friendRef, "Error allocating memory, exiting");

    strcpy(friendRef->data, friendName);    
    friendRef->next = NULL;

    if (*list != NULL)
        friendRef->next = *list;
    *list = friendRef;    
}
void addFriend(Profile* profile, char* friendName){
    addToFriendRefList(&profile->friendsHead, friendName);
    profile->friendsCount += 1;
}
void addPendingRequest(Profile* profile, char* friendName){
    addToFriendRefList(&profile->pendingRequestsHead, friendName);
    profile->pendingRequestsCount += 1;
}

char* serializeProfile(Profile* profile){
    
    int size = USERNAME_LEN*(profile->friendsCount);
    size+= USERNAME_LEN*(profile->pendingRequestsCount);
    size += strlen(profile->status);
    size += strlen(profile->username);

    char* res = (char*)malloc(size*sizeof(char));
    SOCIO_ASSERT(res, "Error allocating memory, exiting");

    res[0] = '\0';
    strcat(res, "Username_");
    strcat(res, profile->username);

    strcat(res, "\nStatus_");
    strcat(res, profile->status);

    strcat(res, "\nFriends_");
    FriendRef* cur = profile->friendsHead;
    for (int i = 0; i < profile->friendsCount; i++){
        strcat(res, cur->data);
        if (i != profile->friendsCount-1)
            strcat(res, LIST_SEPERATOR);
        cur = cur->next;
    }
    
    strcat(res, "\nPending_");
    cur = profile->pendingRequestsHead;
    for (int i = 0; i < profile->pendingRequestsCount; i++){
        strcat(res, cur->data);
        if (i != profile->pendingRequestsCount - 1)
            strcat(res, LIST_SEPERATOR);
        cur = cur->next;
    }

    return res;
}

Profile* newProfile(char* name){
    Profile *p = (Profile*)malloc(sizeof(Profile));
    SOCIO_ASSERT(p, "Error allocating memory, exiting");
    strcpy(p->username, name);
    p->status[0] = '\0';
    p->friendsHead = NULL;
    p->pendingRequestsHead = NULL;
    return p;
}