//
// Created by 남관우 on 2016. 6. 2..
//


#include "User.h"

void InitUser(User *user)
{
    user->idNumber = -1;
    user->sign_up_date = (char*)malloc(sizeof(char) * LEN);
    user->screen_name = (char*)malloc(sizeof(char) * LEN);
    
    strcpy(user->sign_up_date, "Dummy User");
    strcpy(user->screen_name, "Dummy User");
    
    user->next = NULL;      // no linked friend
}

void AddUser(User *user, int id, char* date, char* name)
{
    user->idNumber = id;
    strcpy(user->sign_up_date, date);
    strcpy(user->screen_name, name);
}

void AddFriend(User *main_User, User *add_User)     // AddTail
{
    if(main_User->next == NULL)
        main_User->next = add_User;
    
    else
    {
        User *cur = main_User->next;
        
        while(cur->next != NULL)
            cur = cur->next;
        
        cur->next = add_User;
    }
}