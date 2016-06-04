//
// Created by 남관우 on 2016. 6. 4..
//

#ifndef DS_PROJECT_USER_H
#define DS_PROJECT_USER_H

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include <string.h>

#define TRUE    1
#define FALSE   0
#define LEN     250

typedef struct _userr
{
    int idNumber;
    char sign_up_date[LEN];
    char screen_name[LEN];

    //List *tweet;
    //List *aFriend;

    struct _userr *next;         // link friend
} User;

User *user = (User *) malloc(sizeof(User));       //allocate User
char *str = (char *) malloc(sizeof(char) * LEN);


static int Total_User = 0, Total_Friendship_Records = 0, Total_Tweets = 0;
static int User_index = 0;

FILE *user_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/ETC/user.utf8", "r");
FILE *fren_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/ETC/friend.utf8", "r");
FILE *word_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/ETC/word.utf8", "r");

void InitUser();
void GetTheUserNum();
void GetFriendShipNum();
void GetTweetsNum();
void PrintInterface();
void CloseFile();

#endif //DS_PROJECT_USER_H



/*  
     *  User File Length: 728  -> 182 Users
     *  Fren File Length: 106,360 -> 35,453Link 
     *  Word File Length: 5,232 -> 1,308 Tweets
     */
