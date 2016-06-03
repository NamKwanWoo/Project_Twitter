//
// Created by 남관우 on 2016. 6. 2..
//

#ifndef DS_PROJECT_USER_H
#define DS_PROJECT_USER_H

#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

#define TRUE    1
#define FALSE   0
#define LEN     250

typedef struct _user
{
    int idNumber;
    char sign_up_date[LEN];
    char screen_name[LEN];
    
    struct _user *next;         // link friend
}User;

void InitUser(User *user);
void AddUser(User *, int, char*, char*);
void AddFriend(User *, User *);

#endif //DS_PROJECT_USER_H