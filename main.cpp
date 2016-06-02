#include "User.h"
#include "LinkedList.h"

void Interface();

int main(void)
{
    FILE *user_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/user.utf8", "r");     // User File Length: 728  -> 182 Users
    FILE *fren_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/friend.utf8", "r");   // Fren File Length: 106,360 -> 26,590 Link 
    FILE *word_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/word.utf8", "r");     // Word File Length: 5,232 -> 1,308 Tweets

    User *user = (User *) malloc(sizeof(User));       //allocate User

    int sKey = 0;   // select number
    int Usernum = 0;
    int index = 0;

    if (user_File == NULL || fren_File == NULL || word_File == NULL)
    {
        puts("File does not exits!");       // error
        exit(-1);                           // exit
    }

    InitUser(user);

    char *str = (char *) malloc(sizeof(char) * LEN);
    User *dummy = (User *) malloc(sizeof(User));
    
    int dummy_num = 0;
    
    while(fgets(str, LEN, user_File))
        dummy_num++;
    
    printf("%d %d\n\n\n", dummy_num, dummy_num/4);
    
    while (fgets(str, LEN, user_File))
    {
        if (index == 0)
        {
            dummy->idNumber = (int) atof(str);
            index ++;
        }
        else if (index == 1)
        {
            dummy->sign_up_date = str;
            index ++;
        }
        else if (index == 2)
        {
            dummy->screen_name = str;
            index ++;
        }

        if (index == 3)
        {
            index = 0;                              // init idx
            user->next = dummy;

            Usernum++;
        }
    }
    
    printf("%d\n", Usernum);

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