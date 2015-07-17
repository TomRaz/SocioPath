#ifndef ProfileManager_h
#define ProfileManager_h

#include "Profile.h"

typedef struct profile_list_t{
    Profile profile;
    struct Profile *next;
}ProfileListItem;



typedef struct profileManager_t{    
    ProfileListItem* head;
} ProfileManager;



#endif