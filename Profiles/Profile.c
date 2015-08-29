#include "Profile.h"
#include "../Common/CommonFunctions.h"
#include <stdio.h>
#include <assert.h>

#define USER_NAME_PREFIX_LEN 9
#define STATUS_PREFIX_LEN 7
#define FRIEND_PREFIX_LENGTH 7
#define PENDING_REQ_PREFIX_LENGTH 7

Profile* deserializeProfile(char** lines){
    Profile *p = (Profile*)malloc(sizeof(Profile));
    SOCIO_ASSERT_MEM(p);
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

void addToFriendRefListSortedByName(FriendRef** list, char* friendName){
    FriendRef* friendRef = (FriendRef*)malloc(sizeof(FriendRef));
    SOCIO_ASSERT_MEM(friendRef);

    strcpy(friendRef->data, friendName);    
    friendRef->next = NULL;

    
    if (*list != NULL){
        //insertion sort
        FriendRef* cur = *list;
        FriendRef* prev = NULL;
        while (cur != NULL){
            if (_stricmp(cur->data, friendName)>0){
                break;
            }
            prev = cur;
            cur = cur->next;
            
        }
        if (prev == NULL){
            friendRef->next = cur;
            *list = friendRef;
        }
        else{
            friendRef->next = cur;
            prev->next = friendRef;
        }        
    }
    else{
        *list = friendRef;
    }
    
}
void addFriend(Profile* profile, char* friendName){
    addToFriendRefListSortedByName(&profile->friendsHead, friendName);
    profile->friendsCount += 1;
}
void addPendingRequest(Profile* profile, char* friendName){
    FriendRef* friendRef = (FriendRef*)malloc(sizeof(FriendRef));
    SOCIO_ASSERT_MEM(friendRef);
    strcpy(friendRef->data, friendName);
    friendRef->next = NULL;    
    if (profile->pendingRequestsHead == NULL){
        profile->pendingRequestsHead = friendRef;
    }
    else{
        FriendRef* cur = profile->pendingRequestsHead;
        while (cur->next != NULL){
            cur = cur->next;
        }
        cur->next = friendRef;
    }    
    
    profile->pendingRequestsCount += 1;
}

char* serializeProfile(Profile* profile){
    
    int size = (USERNAME_LEN + SEP_LEN)*(profile->friendsCount);
    size += (USERNAME_LEN + SEP_LEN)*(profile->pendingRequestsCount);
    size += strlen(profile->status);
    size += strlen(profile->username);
    size += USER_NAME_PREFIX_LEN + USER_NAME_PREFIX_LEN + FRIEND_PREFIX_LENGTH + PENDING_REQ_PREFIX_LENGTH + 8;

    char* res = (char*)malloc(size*sizeof(char));
    SOCIO_ASSERT_MEM(res);

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
    SOCIO_ASSERT_MEM(p);
    strcpy(p->username, name);
    p->status[0] = '\0';
    p->friendsHead = NULL;
    p->pendingRequestsHead = NULL;
    return p;
}

bool removeFromFriendRefList(FriendRef** friendList, char* name){
    FriendRef* cur = *friendList;
    FriendRef* prev = NULL;
    while (cur != NULL){
        if (strcmp(name, cur->data) == 0){
            if (prev == NULL){
                *friendList = cur->next;
            }
            else{
                prev->next = cur->next;
            }
            free(cur);
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}
bool removeFriend(Profile* p, char* name){
    if (removeFromFriendRefList(&p->friendsHead, name)){
        p->friendsCount--;
        return true;
    }
    return false;  
}

bool findInFriendsList(FriendRef* head, char* name){
    while (head != NULL){
        if (strcmp(name, head->data) == 0){
            return true;
        }
        head = head->next;
    }
    return false;
}

bool isFriend(Profile* profile, char* name){
    return findInFriendsList(profile->friendsHead, name);
}

bool isFriendRequestPending(Profile* profile, char* name){
    return findInFriendsList(profile->pendingRequestsHead, name);    
}

bool removePendingFriendRequest(Profile* profile, char* name){
    if (removeFromFriendRefList(&(profile->pendingRequestsHead), name)){
        profile->pendingRequestsCount--;
        return true;
    }
    return false;
}
bool acceptFriendRequest(Profile* mine, Profile* other){
    if (!removePendingFriendRequest(mine, other->username))
        return false;
    addFriend(mine, other->username);
    addFriend(other, mine->username);
    return true;    
}

bool rejectFriendRequest(Profile* mine, Profile* other){
    if (!removePendingFriendRequest(mine, other->username)){
        return false;
    }        
    return true;
}