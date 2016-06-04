//
// Created by 남관우 on 2016. 6. 4..
//

#include "User.h"

void InitUser()
{
    user->idNumber = FALSE;
    user->next = NULL;
    //InitList(user->aFriend);
    //InitList(user->tweet);
}

void AddUser(User *user, int id, char *date, char *name)
{
    user->idNumber = id;
    strcpy(user->sign_up_date, date);
    strcpy(user->screen_name, name);
}

void GetTheUserNum()
{
    int index = 0;

    while (fgets(str, LEN, user_File))
    {
        if (strcmp(str, "\n") == 0)
            continue;

        if (index == 3)
        {
            User_index++;
            index = 0;
        }

        if (index == 0)
        {
            (user + User_index)->idNumber = (int) atof(str);
            index++;
        }
        else if (index == 1)
        {
            strcpy((user + User_index)->sign_up_date, str);
            index++;
        }
        else if (index == 2)
        {
            strcpy((user + User_index)->screen_name, str);
            index++;
        }


        Total_User++;                              // link -> number ++    
    }

    Total_User = User_index + 1;                        // Struct group(One User) consists 4 lines
}

void GetFriendShipNum()
{
    while (fgets(str, LEN, fren_File))
    {
        Total_Friendship_Records++;
    }
    Total_Friendship_Records /= 3;
}

void GetTweetsNum()
{
    int index = 0;
    int User_index = 0;     // scope, inner

    while (fgets(str, LEN, word_File))
    {
        /*if (strcmp(str, "\n") == 0)
        {
            Total_Tweets++;
            continue;
        }

        if (index == 3)
        {
            index = 0;
        }

        if (index == 0)
        {
            while(TRUE)
            {
                if(atoi(str) == (user+User_index)->idNumber)
                {
                    break;
                }
                else
                    User_index++;
            }
            index++;
        }
        else if (index == 1)
        { 
            index++;
        }
        else if (index == 2)
        {
            AddData_Tail((user+User_index)->tweet, str);
            index++;
        }*/
        Total_Tweets++;
    }
    Total_Tweets /= 4;
}

void ReadTheDataFile()
{
    printf("%s %d\n", "Total users: ", Total_User);
    printf("%s %d\n", "Total friendship records: ", Total_Friendship_Records);
    printf("%s %d\n", "Total tweets: ", Total_Tweets);
}




void PrintInterface()
{
    puts("0. Read data files");
    puts("1. display statistics");
    puts("2. Top 5 most tweeted words");
    puts("3. Top 5 most tweeted users");
    puts("4. Find users who tweeted a word (e.g., ’연세대’)");
    puts("5. Find all people who are friends of the above users");
    puts("6. Delete users who mentioned a word");
    puts("7. Delete all users who mentioned a word");
    puts("8. Find strongly connected components");
    puts("9. Find shortest path from a given user");
    puts("99. Quit");
    printf("Select Menu: ");
}

int Process()
{
    int sKey;
    scanf("%d", &sKey);

    switch (sKey)
    {
        case 0:
            // 0. ReadDataFiles
            /*Total users: xxx
            Total friendship records: xxx
            Total tweets: xxx*/
            ReadTheDataFile();
            break;

        case 1:
            // 1. Statistics
            /*Average number of friends: xxx
            Minimum friends: xxx
            Maximum number of friends: xxx
            Average tweets per user: xxx
            Minium tweets per user: xxx
            Maximu tweets per user: xxx*/

        case 2:

        case 3:

        case 4:

        case 5:

        case 6:

        case 7:

        case 8:

        case 9:

        case 99:
            puts("Quit the program");
            return FALSE;
            break;

        default:
            break;
    }
    return TRUE;
}

void CloseFile()
{
    fclose(user_File);
    fclose(fren_File);
    fclose(word_File);
    free(user);
    free(str);
}