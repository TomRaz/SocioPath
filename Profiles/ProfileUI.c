#include "ProfileUI.h"
#include "../Common/CommonFunctions.h"
#include <stdio.h>

ProfileUI* newProfileUI(char* username){
    ProfileUI* profileUI = (ProfileUI*)malloc(sizeof(ProfileUI));
    SOCIO_ASSERT_MEM(profileUI);
    //TODO: handle situation in which there is no file, and we create the first one
    profileUI->profileManager = deserializeProfileManager(PROFILES_PATH);
    profileUI->curProfile = getProfile(profileUI->profileManager, username);
    if (profileUI->curProfile == NULL){
        profileUI->curProfile = createProfile(profileUI->profileManager, username);
    }
    return profileUI;
}

void showProfile(ProfileUI* ui, char* friendsStatusHeader){
    printf("Your status: %s\n", ui->curProfile->status);
    printf("%s", friendsStatusHeader);
    char* friendsStatues = getFriendsStatuses(ui->profileManager, ui->curProfile);
    if (friendsStatues != NULL){
        printf("%s\n", friendsStatues);
        free(friendsStatues);
    }
}
bool startProfileUI(ProfileUI* ui){
    printf("Hey %s and welcome to your profile!\n", ui->curProfile->username);
    showProfile(ui, "What's on your friends' minds:\n");
    return mainDialog(ui);
}

bool mainDialog(ProfileUI* ui){
    while (true){
        printOptions();
        char cmd[MAX_COMMAND_SIZE];
        fgets(cmd, MAX_COMMAND_SIZE, stdin);
        //remove trailing newline
        strtok(cmd, "\n");
        if (strcmp(cmd, "$") == 0){
            printf("Exiting, bye");
            return false;
        }
        else if (strcmp(cmd, "#") == 0){
            printf("Logging out");
            return true;
        }
        else if (strcmp(cmd, "printNetwork") == 0){
            printNetwork(ui);
        }
        else if (strcmp(cmd, "profile") == 0){
            showProfile(ui, "Your friends' statuses:\n");
        }
        else if (strcmp(cmd, "status") == 0){
            updateStatusDialog(ui);
        }
        else if (strcmp(cmd, "checkRequests") == 0){
            checkRequestsDialog(ui->profileManager, ui->curProfile);
        }
        else if (strcmp(cmd, "printFriends") == 0){
            printFriends(ui);
        }
        else if (strstr(cmd, "search") != NULL){
            char* userName = extractUsernameFromCmd(cmd);            
            if (!userName)
                continue;
            searchProfile(ui, userName);
        }
        else if (strstr(cmd, "checkStatus") != NULL){
            char* userName = extractUsernameFromCmd(cmd);
            if (!userName)
                continue;
            checkFriendStatus(ui, userName);
        }
        else if (strstr(cmd, "request") != NULL){
            char* userName = extractUsernameFromCmd(cmd);
            if (!userName)
                continue;
            sendFriendRequest(ui, userName);
        }
        else if (strstr(cmd, "unfriend") != NULL){
            char* userName = extractUsernameFromCmd(cmd);
            if (!userName)
                continue;
            unfriend(ui, userName);
        }
        else{
            printf("Command '%s' not recognized, please try again\n", cmd);
        }
            
        printf("Please enter the next command\n");
    }
}

void printOptions(){
    printf("\"profile\" - show your profile.\n");
    printf("\"status\" - update your current status.\n");
    printf("\"checkStatus <friend_username>\" - check the current status of a specific friend, whose username you enter in the place of <friend_username>.\n");
    printf("\"checkRequests\" - check incoming friend requests.\n");
    printf("\"printFriends\" - print the list of your friends(usernames).\n");
    printf("\"search <query>\" - search SocioPath network for a username.\n");
    printf("\"request <username>\" - send a friend request to the given username.\n");
    printf("\"unfriend <friend_username>\" - unfriend the entered friend.\n");
    printf("\"printNetwork\" - print your social network.\n");
    printf("\"#\" - log out and return to the first App screen.\n");
    printf("\"$\" - exit the app\n");
}

char* extractUsernameFromCmd(char* cmd){
    char* spacePtr = strchr(cmd, ' ');
    if (spacePtr == NULL){
        printf("Error parsing the command, please try again\n");
        return NULL;     
    }        
    return spacePtr + 1;
}

void saveData(ProfileUI* ui){
    serializeProfileManager(ui->profileManager, PROFILES_PATH);
}

void printFriends(ProfileUI* ui){
    FriendRef* ref = ui->curProfile->friendsHead;
    printf("Your friends are:\n");
    for (int i = 0; i < ui->curProfile->friendsCount; i++, ref = ref->next){
        printf("%d. %s\n", i+1, ref->data);
    }
}

void searchProfile(ProfileUI* ui, char* name){
    int len;
    Profile** profiles = searchByName(ui->profileManager, name, &len);
    if (len == 0){
        printf("The search for \"%s\" has found no users in SocioPath network :\n", name);
        return;
    }
    printf("The search for \"%s\" has found the following users within the SocioPath network :\n", name);
    for (int i = 0; i < len; i++){
        printf("%d. %s\n", i+1, profiles[i]->username);
    }
    free(profiles);
}

void checkFriendStatus(ProfileUI* ui, char* name){
    Profile* res = getProfile(ui->profileManager, name);
    if (!res){
        printf("Could not find friend %s\n", name);
    }
    else{
        printf("%s status is : '%s'\n", name, res->status);
    }
}

void unfriend(ProfileUI* ui, char* name){
    if (!removeFriend(ui->curProfile, name)){
        printf("%s is not your friend!\n", name);
    }
    else{
        Profile* p = getProfile(ui->profileManager, name);
        if (p != NULL){
            removeFriend(p, ui->curProfile->username);
        }
        printf("You are no longer friend with %s\n", name);
    }
}

void updateStatusDialog(ProfileUI* ui){
    printf("Update your SocioPath status to share with your friends.\n");
    printf("Input: ");
    char newStatus[STATUS_MAX_SIZE+1];
    fgets(newStatus, STATUS_MAX_SIZE + 1, stdin);
    if (strlen(newStatus) != STATUS_MAX_SIZE || newStatus[STATUS_MAX_SIZE - 1] == '\n'){
        //no overflow
        //remove trailing \n
        strtok(newStatus, "\n");
        strcpy(ui->curProfile->status, newStatus);
    }
    else{
        //overflow
        printf("You entered more than %d characters, do you want to use the first %d characters? type yes or no \n", STATUS_MAX_SIZE, STATUS_MAX_SIZE);
        char choice[20];
        fflush(stdin);
        scanf("%s", &choice);
        if (stricmp(choice, "yes") == 0){
            printf("Updating your status\n");
            strcpy(ui->curProfile->status, newStatus);
        }
        else{
            printf("Not updating your status\n");
        }

    }
}

void sendFriendRequest(ProfileUI* ui, char* name){
    //TODO: what about a state in which the user has already sent me a friend request?!
    Profile* prof = getProfile(ui->profileManager, name);
    if (!prof){
        printf("Could not find user %s\n", name);
        return;
    }
    if (isFriend(ui->curProfile, name)){
        printf("You already friend of %s \n", name);
        return;
    }
    if (isFriendRequestPending(prof, ui->curProfile->username)){
        printf("You already sent a friend request to %s \n", name);
        return;
    }
    addPendingRequest(prof, ui->curProfile->username);
    printf("Friend request sent to %s\n", name);
}


void printNetwork(ProfileUI* ui){
    //TODO:figure out how many levels do we need here? is it until we don't find any more people? 
    //complete the function
    printf("Dear %s, your soical network is:\n", ui->curProfile->username);
    printf("You: %s\n", ui->curProfile->username);
    int numOfFriends;
    Profile** friends = getUsersFriends(ui->profileManager, ui->curProfile, &numOfFriends);
    printf("Your Friends:");
    for (int i = 0; i < numOfFriends; i++){
        printf("%s", friends[i]);
        if (i != numOfFriends - 1)
            printf(",");
    }
    printf("\n");

}