#include "CheckRequestsDialog.h"
#include <stdio.h>

Profile** getUserFromProfileList(Profile** profiles, int listLen, char* name){
    for (int i = 0; i < listLen; i++){
        if (strcmp(name, profiles[i]->username) == 0){
            return profiles[i];
        }
    }
    return NULL;
}

Profile* parseAcceptOrReject(char* cmd, Profile** profiles, int numOfFriends){
    int splittedSize;
    char** splitted = splitStr2(cmd, "::", &splittedSize);

    Profile* prof = getUserFromProfileList(profiles, numOfFriends, splitted[1]);
    if (prof == NULL){
        printf("User %s didn't request your friend request, please try again\n", splitted[1]);
        return NULL;
    }
    free2Darr(splitted, splittedSize);
    return prof;
}

Profile** fetchAndPrintFriendRequests(ProfileManager* manager, Profile* curProfile, int* numberOfFriends){
    Profile** profiles = getUsersFriendRequests(manager, curProfile, numberOfFriends);
    if (*numberOfFriends == 0){
        printf("You don't have any new friend requests\n");
        return NULL;
    }
    printf("Dear %s, you have %d friend requests.\n", curProfile->username, *numberOfFriends);
    printf("The pending requests are from the users:\n");
    for (int i = 0; i < *numberOfFriends; i++){
        printf("%d. %s\n", i + 1, profiles[i]->username);
    }
    printf("To approve the request, enter \"approve::<username>\".\n");
    printf("To refuse and delete the request, enter \"refuse::<username>\".\n");
    printf("To go back to the main selection menu, enter \"&\".\n");
    return profiles;

}

void askForUserAction(Profile** profiles, Profile* curProfile, int numOfFriends){
    while (true){
        char cmd[MAX_COMMAND_SIZE];
        fgets(cmd, MAX_COMMAND_SIZE, stdin);
        //remove trailing newline
        strtok(cmd, "\n");
        if (strstr(cmd, "approve::") != NULL){
            Profile* p = parseAcceptOrReject(cmd, profiles, numOfFriends);
            if (p){
                if (acceptFriendRequest(curProfile, p)){                
                    printf("%s Friend request accepted\n", p->username);
                    return;
                }
                else{
                    printf("Unexpected error occured, exiting\n");
                    exit(1);
                }
            }
        }
        else if (strstr(cmd, "refuse::") != NULL){
            Profile* p = parseAcceptOrReject(cmd, profiles, numOfFriends);
            if (p){
                if (rejectFriendRequest(curProfile, p)){
                    printf("%s Friend request rejected\n", p->username);
                    return;
                }
                else{
                    printf("Unexpected error occured, exiting\n");
                    exit(1);
                }
            }
        }
        else if (strcmp(cmd, "&") == 0){
            printf("Returning to main menu\n");
            return;
        }
        else{
            printf("Invalid cmd '%s', please try again\n", cmd);
        }
    }
}

void checkRequestsDialog(ProfileManager* manager, Profile* curProfile){
    int numOfFriends;
    Profile** profiles = fetchAndPrintFriendRequests(manager, curProfile, &numOfFriends);
    if (!profiles){
        free(profiles);
        return;
    }        
    askForUserAction(profiles, curProfile, numOfFriends);
    free(profiles);
    

}