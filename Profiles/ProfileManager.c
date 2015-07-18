#include "ProfilesManager.h"
#include "../Common/CommonFunctions.h"
#include <stdio.h>

ProfileListItem* add(ProfileListItem* list, Profile* item){
    ProfileListItem* listItem = malloc(sizeof(ProfileListItem));
    SOCIO_ASSERT_MEM(listItem);
    listItem->profile = item;
    listItem->next = NULL;    
    if (list == NULL)
        return listItem;
    listItem->next = list;    
    return listItem;
}

void addProfile(ProfileManager* manager, Profile* profile){
    manager->head = add(manager->head, profile);
    manager->profilesCount += 1;
}

ProfileManager* deserializeProfileManager(char* path){
    int lines;
    char** data = readAllLines(path, &lines);    
    if (!lines){
        printf("Error reading from file, exiting");
        exit(1);
    }    
    if (lines % 4 != 0){
        printf("Wrong number of lines in profile file, exiting");
        exit(1);
    }
    ProfileManager* manager = (ProfileManager*)malloc(sizeof(ProfileManager));
    SOCIO_ASSERT_MEM(manager);
    manager->head = NULL;
    manager->profilesCount = 0;
    for (int i = 0; i < lines; i+=4){
        Profile* p = deserializeProfile(data+i);
        addProfile(manager, p);        
    }
    return manager;
}

void freeProfileManager(ProfileManager* manager){
    ProfileListItem* cur = manager->head;
    while (cur != NULL){
        ProfileListItem* next = cur->next;
        freeProfile(cur->profile);
        free(cur);
        cur = next;
    }
    free(manager);
}

void serializeProfileManager(ProfileManager* manager, char* path){
    FILE *f = fopen(path, "w");
    SOCIO_ASSERT(f, "Error opening profiles.txt file");
    ProfileListItem* cur = manager->head;
    for (int i = 0; i < manager->profilesCount; i++){
        char* profileTxt = serializeProfile(cur->profile);
        fprintf(f, "%s", profileTxt);
        if (i != manager->profilesCount - 1)
            fprintf(f, "\n");
        free(profileTxt);
        cur = cur->next;        
    }
    fclose(f);
}

Profile* getProfile(ProfileManager* manager, char* name){
    ProfileListItem* cur = manager->head;
    while (cur != NULL){
        if (strcmp(cur->profile->username, name) == 0){
            return cur->profile;
        }
        cur = cur->next;
    }
    return NULL;
}

Profile* createProfile(ProfileManager* manager, char* name){
    Profile* p = newProfile(name);
    addProfile(manager, p);
    return p;
}

char* getFriendsStatuses(ProfileManager* manager, Profile* profile){
    int numOfFriends;
    Profile** profiles = getUsersFriends(manager, profile, &numOfFriends);
    if (numOfFriends == 0)
        return NULL;
    char* res = (char*)malloc(STATUS_MAX_SIZE * numOfFriends * sizeof(char));
    res[0] = '\0';
    for (int i = 0; i < numOfFriends; i++){
        strcat(res, profiles[i]->username);
        strcat(res, ": ");
        strcat(res, profiles[i]->status);
        if (i != numOfFriends - 1)
            strcat(res,"\n");
    }
    free(profiles);
    return res;
}

Profile** getUsersFriends(ProfileManager* manager, Profile* profile, int* numOfFriends){
    
    Profile** res = NULL;
    
    int len = 0;
    FriendRef* cur = profile->friendsHead;
    while (cur != NULL){
        res = (Profile**)realloc(res, (len+1)*sizeof(Profile*));
        SOCIO_ASSERT_MEM(res);
        res[len] = getProfile(manager, cur->data);
        SOCIO_ASSERT(res[len], "Found a friend without a profile, abnormal state, exiting");
        cur = cur->next;
        len++;
    }
    *numOfFriends = len;
    return res;
}

Profile** searchByName(ProfileManager* manager, char* name, int *numOfProfiles){
    Profile** res = NULL;
    ProfileListItem* cur = manager->head;
    int len = 0;
    while (cur != NULL){
        if (stristr(cur->profile->username, name) != NULL){
            res = (Profile**)realloc(res, (len + 1)*sizeof(Profile*));
            SOCIO_ASSERT_MEM(res);
            res[len++] = getProfile(manager, cur->profile->username);
        }        
        cur = cur->next;        
    }
    *numOfProfiles = len;
    return res;
}