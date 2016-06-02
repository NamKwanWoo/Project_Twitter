//
// Created by 남관우 on 2016. 6. 2..
//

#ifndef DS_PROJECT_USER_H
#define DS_PROJECT_USER_H

#define TRUE    1
#define FALSE   0
#define LEN     30

typedef struct _user
{
    int idNumber;
    char sign_up_date[LEN];
    char screen_name[LEN];
    
}User;

void InitUser(User *user);
void PushUser(User *, int, char*, char*);

#endif //DS_PROJECT_USER_H
