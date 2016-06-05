#include "User.h"

static int Total_User = 0, Total_Friendship_Records = 0, Total_Tweets = 0;
static int User_index = 0;

void Interface();

void GetTheUserNum(User *user, FILE *user_File, char *str);

void GetFriendShipNum(User *user, FILE *fren_File, char *str);

void GetTweetsNum(User *user, FILE *word_File, char *str);

void ReadTheDataFile();

int Process();

int main(void)
{
    FILE *user_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/ETC/user.utf8", "r");     //182     
    FILE *fren_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/ETC/friend.utf8", "r");   //35,453 
    FILE *word_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/ETC/word.utf8", "r");     //1,308
    User *user = (User *) malloc(sizeof(User));       //allocate User
    char *str = (char *) malloc(sizeof(char) * LEN);

    InitUser(user);

    GetTheUserNum(user, user_File, str);
    GetFriendShipNum(user, fren_File, str);
    GetTweetsNum(user, word_File, str);

    do { Interface(); } while (Process());
    
    printf("%d\n\n", user->tweetsNum);

    return 0;
}

void Interface()
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

void GetTheUserNum(User *user, FILE *user_File, char *str)
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
            (user + User_index)->idNumber = atoi(str);
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

void GetFriendShipNum(User *user, FILE *fren_File, char *str)
{
    while (fgets(str, LEN, fren_File))
    {
        Total_Friendship_Records++;
    }
    Total_Friendship_Records /= 3;
}

void GetTweetsNum(User *user, FILE *word_File, char *str)
{
    int index = 0;
    int userIndex = 0;

    while (fgets(str, LEN, word_File))
    {
        if (strcmp(str, "\n") == 0 || strcmp(str, "\r\n") == 0)
        {
            Total_Tweets++;
            continue;
        }

        if (index == 3) { index = 0; }

        if (index == 0)
        {
            if( (user + userIndex)->idNumber == atoi(str))
                (user + userIndex)->tweetsNum ++;
                
            else
            {
                userIndex = 0;
                while ((user + userIndex)->idNumber != atoi(str))
                    userIndex++;

                (user + userIndex)->tweetsNum++;
            }
            index++;
        }
        else if (index == 1) { index++; }
            
        else if (index == 2) 
        { 
            //strcpy( (user+userIndex)->tweetWord[(user+userIndex)->tweetsNum - 1], str );
            index++; 
        }

        Total_Tweets++;
    }
    
    Total_Tweets /= 4;
}


void ReadTheDataFile()
{
    NewLine
    printf("%s %d\n", "Total users: ", Total_User);
    printf("%s %d\n", "Total friendship records: ", Total_Friendship_Records);
    printf("%s %d\n", "Total tweets: ", Total_Tweets);
    NewLine
}

int Process()
{
    int sKey;
    scanf("%d", &sKey);

    switch (sKey)
    {
        case 0:
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
            NewLine
            puts("Quit the program");
            return FALSE;

        default:
            break;
    }
    return TRUE;
}