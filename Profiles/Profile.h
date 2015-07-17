#ifndef Profile_h
#define Profile_h

#include "..\Common\consts.h"

typedef struct profile_t{
    char username[USERNAME_LEN + 1];
    char status[STATUS_MAX_SIZE + 1]; //password is saved AFTER encryption

} Profile;


#endif