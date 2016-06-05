#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE    1
#define FALSE   0
#define LEN     250
#define NewLine     printf("\n\n");

typedef char *Data;

static int Total_User = 0, Total_Friendship_Records = 0, Total_Tweets = 0;
static int User_index = 0;

typedef struct _list
{
    Data data;
    struct _list *next;
} Node;

typedef struct _linkedList
{
    Node *head;
    Node *tail;
    Node *cur;

    int numOfData;
} LinkedList;

typedef LinkedList List;

typedef struct _user
{
    int idNumber;
    char sign_up_date[LEN];
    char screen_name[LEN];

    List tweet;
    List aFriend;

    //char tweetWord[1000][LEN];
    //int aFriend[1000];

    int tweetsNum;
    int friendsNum;

    struct _user *next;         // link friend
} User;


void Interface();

void GetTheUserNum(User *user, FILE *user_File, char *str);

void GetFriendShipNum(User *user, FILE *fren_File, char *str);

void GetTweetsNum(User *user, FILE *word_File, char *str);

void ReadTheDataFile();

int Process();

void InitUser(User *user);

void AddUser(User *, int, char *, char *);

void AddFriend(User *, User *);

void InitList(List *);

int IsListEmpty(List *);

void AddData_Head(List *, Data data);

void AddData_Tail(List *, Data data);

void Add_alphabeticalOrder(List *list, Data data);

Data DeleteSpecData(List *list, Data data);

Data DeleteData_Head(List *);

Data DeleteData_Tail(List *);

Data HeadData(List *);

Data TailData(List *);


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
    int i;

    for (i = 0; i < User_index; i++)
    {
        InitList(&(user + i)->tweet);
        (user + i)->tweet.numOfData = 0;
    }

    userIndex = 0;
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
            if ((user + userIndex)->idNumber == atoi(str))
                (user + userIndex)->tweetsNum++;

            else
            {
                userIndex = 0;
                while ((user + userIndex)->idNumber != atoi(str) && (user+userIndex) != NULL)
                    userIndex++;

                (user + userIndex)->tweetsNum++;
            }
            index++;
        }
        else if (index == 1) { index++; }

        else if (index == 2)
        {
            AddData_Tail(&(user + userIndex)->tweet, str);
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

void InitUser(User *user)
{
    user->idNumber = -1;

    user->friendsNum = 0;
    user->tweetsNum = 0;

    strcpy(user->sign_up_date, "Dummy User");
    strcpy(user->screen_name, "Dummy User");

    user->next = NULL;      // no linked friend
}

void AddUser(User *user, int id, char *date, char *name)
{
    user->idNumber = id;
    strcpy(user->sign_up_date, date);
    strcpy(user->screen_name, name);
}

void AddFriend(User *main_User, User *add_User)     // AddTail
{
    if (main_User->next == NULL)
        main_User->next = add_User;

    else
    {
        User *cur = main_User->next;

        while (cur->next != NULL)
            cur = cur->next;

        cur->next = add_User;
    }
}

void InitList(List *list)
{
    list = (List *) malloc(sizeof(List));

    list->head = NULL;
    list->tail = NULL;
    list->cur = NULL;

    list->numOfData = 0;
}

int IsListEmpty(List *list)
{
    if (list->numOfData == 0)
        return TRUE;
    else
        return FALSE;
}

void AddData_Head(List *list, Data data)
{
    Node *addNode = (Node *) malloc(sizeof(Node));
    addNode->data = (char *) malloc(sizeof(char) * LEN);

    addNode->next = NULL;
    addNode->data = data;

    if (IsListEmpty(list))
    {
        list->head = addNode;
        list->tail = addNode;
    }
    else
    {
        addNode->next = list->head;
        list->head = addNode;
    }

    (list->numOfData)++;
}

void AddData_Tail(List *list, Data data)
{
    Node *addNode = (Node *) malloc(sizeof(Node));
    addNode->data = (char *) malloc(sizeof(char) * LEN);

    addNode->next = NULL;
    addNode->data = data;

    if (IsListEmpty(list))
    {
        list->head = addNode;
        list->tail = addNode;
    }
    else
    {
        list->tail->next = addNode;
        list->tail = addNode;
    }

    (list->numOfData)++;
}


Data DeleteData_Head(List *list)
{
    Node *deleteNode;
    Data delData;

    if (IsListEmpty(list))
        return FALSE;

    deleteNode = list->head;
    delData = list->head->data;
    list->head = list->head->next;

    free(deleteNode);
    //free(delData);
    (list->numOfData)--;
    return delData;
}

Data DeleteData_Tail(List *list)
{
    Node *delNode;
    Data delData;

    if (IsListEmpty(list))
        return FALSE;

    delNode = list->tail;
    delData = list->tail->data;

    list->cur = list->head;
    while (list->cur->next != list->tail)
        list->cur = list->cur->next;

    list->tail = list->cur;

    free(delNode);

    (list->numOfData)--;
    return delData;
}

Data DeleteSpecData(List *list, Data data)
{
    Node *delNode;
    Data delData;

    list->cur = list->head;

    if (list->cur == NULL)
        return NULL;

    else if (list->numOfData == 1)
    {
        delNode = list->head;
        delData = list->head->data;

        list->head = NULL;
        list->tail = NULL;
    }

    else if (list->cur->data == data)
    {
        delNode = list->cur;
        delData = list->cur->data;

        list->head = list->head->next;
    }

    else
    {
        while (list->cur != NULL && list->cur->data != data)
            list->cur = list->cur->next;

        if (list->cur == NULL)
            return NULL;

        Node *before = list->head;
        while (before->next != list->cur)
            before = before->next;

        delNode = list->cur;
        delData = list->cur->data;

        if (list->cur == list->tail)
            list->tail = before;

        before->next = list->cur->next;
    }

    free(delNode);
    (list->numOfData)--;

    return delData;
}

Data HeadData(List *list)
{
    if (IsListEmpty(list))
        return FALSE;
    return list->head->data;
}

Data TailData(List *list)
{
    if (IsListEmpty(list))
        return FALSE;
    return list->tail->data;
}