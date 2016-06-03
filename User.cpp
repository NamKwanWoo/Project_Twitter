//
// Created by 남관우 on 2016. 6. 2..
//


#include "User.h"

void InitUser(User *user)
{
    
    
    (user)->userInfo = (UserInfo*)malloc(sizeof(UserInfo));
    (user)->aFriend = (Friend*)malloc(sizeof(Friend));
    (user)->tweet = (Tweet*)malloc(sizeof(Tweet));
    
    user->userInfo->idNumber = -1;
    
    user->tweet->numOfTweets= 0;
    
    user->aFriend->next = NULL;      // no linked friend
    user->aFriend->numOfFriend= 0;
}

void AddUser(User *user, int id, char* date, char* name)
{
    user->userInfo->idNumber = id;
    strcpy(user->userInfo->sign_up_date, date);
    strcpy(user->userInfo->screen_name, name);
}

/*void AddFriend(User *main_User, User *add_User)     // AddTail
{
    if(main_User->aFriend->next == NULL)
        main_User->aFriend->next = (Friend*)add_User->aFriend;
    
    else
    {
        User *cur = main_User->aFriend->next;
        
        while(cur->next != NULL)
            cur = cur->next;
        
        cur->next = add_User;
    }
}*/

void SetTheTweetNum(User *user, FILE *fp, int Total_User)
{
    int i;
    char *str = (char*)malloc(sizeof(char) * LEN);
    
    for(i=0; i<Total_User; i++)
    {
        
    }
    
}