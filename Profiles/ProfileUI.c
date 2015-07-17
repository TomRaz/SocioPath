#include "ProfileUI.h"
#include "../Common/CommonFunctions.h"


ProfileUI* newProfileUI(char* username){
    ProfileUI* profileUI = (ProfileUI*)malloc(sizeof(ProfileUI));
    SOCIO_ASSERT_MEM(profileUI);
    profileUI->profileManager = deserializeProfileManager(PROFILES_PATH);
    profileUI->curProfile = getProfile(profileUI->profileManager, username);
    if (profileUI->curProfile == NULL){
        profileUI->curProfile = createProfile(profileUI->profileManager, username);
    }
    return profileUI;
}

void startProfileUI(ProfileUI* ui){
    printf("Hey %s and welcome to your profile!\n", ui->curProfile->username);
    printf("Your status: %s\n", ui->curProfile->status);
    printf("What's on your friends' minds:\n");
    char* friendsStatues = getFriendsStatuses(ui->profileManager, ui->curProfile);
    if (friendsStatues != NULL){
        printf("%s\n", friendsStatues);
        free(friendsStatues);
    }
    mainDialog(ui);
}

void mainDialog(ProfileUI* ui){
    printOptions();
    char cmd[MAX_COMMAND_SIZE];
    scanf("%200[^\n]", cmd);
    if (strcmp(cmd, "$") == 0){
        printf("Exiting, bye");
        return;
    }
    else if (strcmp(cmd, "#") == 0){
        //TODO add logout
    }
    else if (strcmp(cmd, "printNetwork") == 0){
        //printNetwork(ui);
    }
    else if (strcmp(cmd, "profile") == 0){
        //showProfile(ui);
    }
    else if (strcmp(cmd, "status") == 0){
        //updateStatusDialog(ui);
    }
    else if (strcmp(cmd, "checkRequests") == 0){
        //checkRequestsDialog(ui);
    }
    else if (strcmp(cmd, "printFriends") == 0){
        //printFriends(ui);
    }
    else if (strstr(cmd, "search") != NULL){
        char* userName = extractUsernameFromCmd(cmd);        
        //searchFriend(ui);
    }
    else if (strstr(cmd, "checkStatus") != NULL){
        char* userName = extractUsernameFromCmd(cmd);
        //checkFriendStatus(ui);
    }  
    else if (strstr(cmd, "request") != NULL){
        char* userName = extractUsernameFromCmd(cmd);
        //sendFriendRequest(ui);
    }
    else if (strstr(cmd, "unfriend") != NULL){
        char* userName = extractUsernameFromCmd(cmd);
        //unfriend(ui);
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
    SOCIO_ASSERT(spacePtr, "Error parsing the command, exiting");
    return spacePtr + 1;
}

void saveData(ProfileUI* ui){
    serializeProfileManager(ui->profileManager, PROFILES_PATH);
}