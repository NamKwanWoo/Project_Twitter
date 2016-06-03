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

typedef struct _info
{
    int idNumber;
    char sign_up_date[LEN];
    char screen_name[LEN];
}UserInfo;

typedef struct _tweets
{
    char upload_date[LEN];
    char word[LEN];
    int numOfTweets;
}Tweet;

typedef struct _friend
{
    int id;
    int numOfFriend;
    struct _freind *next;
}Friend;


typedef struct _user
{
    UserInfo *userInfo;
    Tweet *tweet;
    Friend *aFriend;
}User;

void InitUser(User *user);
void AddUser(User *, int, char*, char*);
void AddFriend(User *, User *);
void SetTheTweetNum(User*, FILE*, int);

#endif //DS_PROJECT_USER_H
