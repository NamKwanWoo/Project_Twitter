/*  
     *  User File Length: 728  -> 182 Users
     *  Fren File Length: 106,360 -> 35,453Link 
     *  Word File Length: 5,232 -> 1,308 Tweets
     */


#include "User.h"
#include "LinkedList.h"

void Interface();

void InputUserInfo(User *, FILE *, char *);

void GetFriendShipNum(FILE *, char *);

void GetTweetsNum(FILE *, char *);

void CloseFile(FILE *, FILE *, FILE *);

static int Total_User = 0, Total_Friendship_Records = 0, Total_Tweets = 0;
static int User_index = 0;

int main(void)
{
    FILE *user_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/user.utf8", "r");
    FILE *fren_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/friend.utf8", "r");
    FILE *word_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/word.utf8", "r");

    User *user = (User *) malloc(sizeof(User));       //allocate User
    char *str = (char *) malloc(sizeof(char) * LEN);

    int sKey = 0;   // select number

    if (!user_File || !fren_File || !word_File)
    {
        puts("File does not exits!");       // error
        exit(-1);                           // exit
    }

    InitUser(user);
    InputUserInfo(user, user_File, str);
    GetFriendShipNum(fren_File, str);
    GetTweetsNum(word_File, str);

    Interface();    // Show Interface
    sKey = getchar();

    // Enter the select menu -> screen clear working yet
    switch (sKey)
    {
        case 0:

        case 1:

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
            break;

        default:
            break;
    }

    free(str);
    free(user);
    CloseFile(user_File, fren_File, word_File);
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

void InputUserInfo(User *user, FILE *user_File, char *str)
{
    int index = 0;

    while (fgets(str, LEN, user_File))
    {
        if (strcmp(str, "\n") == 0)
            continue;
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


        if (index == 3)
        {
            User_index++;
            //(user + User_index) = (User*)malloc(sizeof(User));
            index = 0;
        }

        Total_User++;                              // link -> number ++    
    }

    Total_User = User_index;                        // Struct group(One User) consists 4 lines
}

void GetFriendShipNum(FILE *fren_File, char *str)
{
    while (fgets(str, LEN, fren_File))
        Total_Friendship_Records++;
    Total_Friendship_Records /= 3;
}

void GetTweetsNum(FILE *word_File, char *str)
{
    while (fgets(str, LEN, word_File))
        Total_Tweets++;
    Total_Tweets /= 4;
}

void CloseFile(FILE *user_File, FILE *fren_File, FILE *word_File)
{
    fclose(user_File);
    fclose(fren_File);
    fclose(word_File);
}
