#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN     250
#define TRUE    1
#define FALSE   0
#define NewLine     printf("\n\n");

enum nodeColor
{
    RED,
    BLACK
};

typedef char *Data;

typedef struct _node
{
    char *data;
    int idNum;

    struct _node *next;
} Node;

typedef struct _list
{
    Node *head;
    Node *cur;
    Node *tail;

    int numOfData;
} List;


typedef struct _user
{
    int idNumber;
    char sign_up_date[LEN];
    char screen_name[LEN];

    int tweetsNum;
    int friendsNum;

    List *tweet_Word;
    List *friendShip;

    struct _user *next;         // link friend
} User;

struct rbNode
{
    User *data;
    int color;
    struct rbNode *link[2];
};

struct rbNode *root = NULL;

struct rbNode *createNode(User *data)
{
    struct rbNode *newnode;

    newnode = (struct rbNode *) malloc(sizeof(struct rbNode));
    newnode->data = data;
    newnode->color = RED;
    newnode->link[0] = newnode->link[1] = NULL;
    return newnode;
}


static int Total_User = 0, Total_Friendship_Records = 0, Total_Tweets = 0;
static int User_index = 0;

FILE *user_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/ETC/user.utf8", "r");     //182     
FILE *fren_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/ETC/friend.utf8", "r");   //35,453 
FILE *word_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/ETC/word.utf8", "r");     //1,308

User *user = (User *) malloc(sizeof(User));       //allocate User
char *str = (char *) malloc(sizeof(char) * LEN);

List *tweet = (List *) malloc(sizeof(List));
List *aFriend = (List *) malloc(sizeof(List));

void insertion(User *data)
{
    struct rbNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
    int dir[98], ht = 0, index;
    ptr = root;
    if (!root)
    {
        root = createNode(data);
        return;
    }
    stack[ht] = root;
    dir[ht++] = 0;

    while (ptr != NULL)
    {
        if (ptr->data->idNumber == data->idNumber)
        {
            printf("Duplicates Not Allowed!!\n");
            return;
        }
        index = (data->idNumber - ptr->data->idNumber) > 0 ? 1 : 0;
        stack[ht] = ptr;
        ptr = ptr->link[index];
        dir[ht++] = index;
    }

    /* insert the new node */
    stack[ht - 1]->link[index] = newnode = createNode(data);


    while ((ht >= 3) && (stack[ht - 1]->color == RED))
    {
        if (dir[ht - 2] == 0)
        {
            yPtr = stack[ht - 2]->link[1];
            if (yPtr != NULL && yPtr->color == RED)
            {
                /*
                 * Red node having red child. B- black, R-red
                 *     B                R
                 *    / \             /   \
                 *   R   R  =>     B     B
                 *  /               /   
                 * R               R
                 */
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            } else
            {
                if (dir[ht - 1] == 0)
                {
                    yPtr = stack[ht - 1];
                } else
                {
                    /*
                     * XR - node X with red color
                     * YR - node Y with red color
                     * Red node having red child
                     *(do single rotation left b/w X and Y)
                     *         B             B
                     *        /             /
                     *      XR     =>      YR
                     *        \           /
                     *         YR        XR
                     * one more additional processing will be
                     * performed after this else part.  Since
                     * we have red node (YR) with red child(XR)
                     */
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[1];
                    xPtr->link[1] = yPtr->link[0];
                    yPtr->link[0] = xPtr;
                    stack[ht - 2]->link[0] = yPtr;
                }
                /*
                 *  Red node(YR) with red child (XR) - single
                 *  rotation b/w YR and XR for height balance. Still,
                 *  red node (YR) is having red child.  So, change the
                 *  color of Y to black and Black child B to Red R
                 *          B           YR          YB
                 *         /           /  \        /  \
                 *        YR  =>   XR   B  =>  XR  R
                 *       /
                 *      XR
                 */
                xPtr = stack[ht - 2];
                xPtr->color = RED;
                yPtr->color = BLACK;
                xPtr->link[0] = yPtr->link[1];
                yPtr->link[1] = xPtr;
                if (xPtr == root)
                {
                    root = yPtr;
                } else
                {
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        } else
        {
            yPtr = stack[ht - 2]->link[0];
            if ((yPtr != NULL) && (yPtr->color == RED))
            {
                /*
                 * Red node with red child
                 *        B             R
                 *      /   \         /   \
                 *     R     R =>  B     B
                 *             \              \
                 *              R              R
                 *
                 */
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            } else
            {
                if (dir[ht - 1] == 1)
                {
                    yPtr = stack[ht - 1];
                } else
                {
                    /*
                     * Red node(XR) with red child(YR) 
                     *   B          B
                     *    \          \
                     *     XR  => YR
                     *    /            \
                     *   YR             XR
                     * Single rotation b/w XR(node x with red color) & YR
                     */
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[0];
                    xPtr->link[0] = yPtr->link[1];
                    yPtr->link[1] = xPtr;
                    stack[ht - 2]->link[1] = yPtr;
                }
                /*
                 *   B              YR          YB
                 *    \             /  \        /  \
                 *     YR  =>   B   XR => R    XR
                 *      \
                 *       XR
                 * Single rotation b/w YR and XR and change the color to
                 * satisfy rebalance property.
                 */
                xPtr = stack[ht - 2];
                yPtr->color = BLACK;
                xPtr->color = RED;
                xPtr->link[1] = yPtr->link[0];
                yPtr->link[0] = xPtr;
                if (xPtr == root)
                {
                    root = yPtr;
                } else
                {
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
    }
    root->color = BLACK;
}

void deletion(User *data)
{
    struct rbNode *stack[98], *ptr, *xPtr, *yPtr;
    struct rbNode *pPtr, *qPtr, *rPtr;
    int dir[98], ht = 0, diff, i;
    enum nodeColor color;

    if (!root)
    {
        printf("Tree not available\n");
        return;
    }

    ptr = root;
    /* search the node to delete */
    while (ptr != NULL)
    {
        if ((data->idNumber - ptr->data->idNumber) == 0)
            break;
        diff = (data->idNumber - ptr->data->idNumber) > 0 ? 1 : 0;
        stack[ht] = ptr;
        dir[ht++] = diff;
        ptr = ptr->link[diff];
    }

    if (ptr->link[1] == NULL)
    {
        /* node with no children */
        if ((ptr == root) && (ptr->link[0] == NULL))
        {
            free(ptr);
            root = NULL;
        } else if (ptr == root)
        {
            /* deleting root - root with one child */
            root = ptr->link[0];
            free(ptr);
        } else
        {
            /* node with one child */
            stack[ht - 1]->link[dir[ht - 1]] = ptr->link[0];
        }
    } else
    {
        xPtr = ptr->link[1];
        if (xPtr->link[0] == NULL)
        {
            /*
             * node with 2 children - deleting node 
             * whose right child has no left child
             */
            xPtr->link[0] = ptr->link[0];
            color = (nodeColor) xPtr->color;
            xPtr->color = ptr->color;
            ptr->color = color;

            if (ptr == root)
            {
                root = xPtr;
            } else
            {
                stack[ht - 1]->link[dir[ht - 1]] = xPtr;
            }

            dir[ht] = 1;
            stack[ht++] = xPtr;
        } else
        {
            /* deleting node with 2 children */
            i = ht++;
            while (1)
            {
                dir[ht] = 0;
                stack[ht++] = xPtr;
                yPtr = xPtr->link[0];
                if (!yPtr->link[0])
                    break;
                xPtr = yPtr;
            }

            dir[i] = 1;
            stack[i] = yPtr;
            if (i > 0)
                stack[i - 1]->link[dir[i - 1]] = yPtr;

            yPtr->link[0] = ptr->link[0];
            xPtr->link[0] = yPtr->link[1];
            yPtr->link[1] = ptr->link[1];

            if (ptr == root)
            {
                root = yPtr;
            }

            color = (nodeColor) yPtr->color;
            yPtr->color = ptr->color;
            ptr->color = color;
        }
    }
    if (ht < 1)
        return;
    if (ptr->color == BLACK)
    {
        while (1)
        {
            pPtr = stack[ht - 1]->link[dir[ht - 1]];
            if (pPtr && pPtr->color == RED)
            {
                pPtr->color = BLACK;
                break;
            }

            if (ht < 2)
                break;

            if (dir[ht - 2] == 0)
            {
                rPtr = stack[ht - 1]->link[1];

                if (!rPtr)
                    break;

                if (rPtr->color == RED)
                {
                    /*
                     * incase if rPtr is red, we need
                     * change it to black..
                     *    aB                 rPtr (red)  rPtr(black)
                     *   /  \      =>      /    \  =>    /   \
                     *  ST  rPtr(red)  aB    cB      aR   cB
                     *       /  \       /  \           /  \
                     *     bB  cB   ST  bB       ST  bB
                     *  ST - subtree
                     *  xB - node x with Black color
                     *  xR - node x with Red color
                     * the above operation will simply rebalace
                     * operation in RB tree
                     */
                    stack[ht - 1]->color = RED;
                    rPtr->color = BLACK;
                    stack[ht - 1]->link[1] = rPtr->link[0];
                    rPtr->link[0] = stack[ht - 1];

                    if (stack[ht - 1] == root)
                    {
                        root = rPtr;
                    } else
                    {
                        stack[ht - 2]->link[dir[ht - 2]] = rPtr;
                    }
                    dir[ht] = 0;
                    stack[ht] = stack[ht - 1];
                    stack[ht - 1] = rPtr;
                    ht++;

                    rPtr = stack[ht - 1]->link[1];
                }


                if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) &&
                    (!rPtr->link[1] || rPtr->link[1]->color == BLACK))
                {
                    /*
                     *      rPtr(black)         rPtr(Red)
                     *     /    \          =>  /    \
                     *    B      B            R      R
                     *
                     */
                    rPtr->color = RED;
                } else
                {
                    if (!rPtr->link[1] || rPtr->link[1]->color == BLACK)
                    {
                        /*
                         * Below is a subtree. rPtr with red left child
                         * single rotation right b/w yR and rPtr  &
                         * change the color as needed
                         *        wR                        wR
                         *       /  \                      /  \
                         *      xB   rPtr(Black) =>   xB  yB
                         *     / \   /  \               /  \  /  \
                         *    a   b yR   e           a   b c   rPtr(Red)
                         *          /  \                          /  \
                         *         c    d                        d    e
                         */
                        qPtr = rPtr->link[0];
                        rPtr->color = RED;
                        qPtr->color = BLACK;
                        rPtr->link[0] = qPtr->link[1];
                        qPtr->link[1] = rPtr;
                        rPtr = stack[ht - 1]->link[1] = qPtr;
                    }
                    /*
                     * Below is a subtree. rPtr with Right red child
                     * single rotation b/w rPtr & wR and change colors
                     *       wR (stack[ht-1])      rPtr(Red)
                     *     /   \                        /    \
                     *    xB    rPtr(black)     wB     yB
                     *   / \   /  \        =>    /   \   /  \
                     *  a   b c    yR         xB    c d    e
                     *              /  \       /  \
                     *             d    e    a    b
                     */
                    rPtr->color = stack[ht - 1]->color;
                    stack[ht - 1]->color = BLACK;
                    rPtr->link[1]->color = BLACK;
                    stack[ht - 1]->link[1] = rPtr->link[0];
                    rPtr->link[0] = stack[ht - 1];
                    if (stack[ht - 1] == root)
                    {
                        root = rPtr;
                    } else
                    {
                        stack[ht - 2]->link[dir[ht - 2]] = rPtr;
                    }
                    break;
                }
            } else
            {
                rPtr = stack[ht - 1]->link[0];
                if (!rPtr)
                    break;

                if (rPtr->color == RED)
                {
                    stack[ht - 1]->color = RED;
                    rPtr->color = BLACK;
                    stack[ht - 1]->link[0] = rPtr->link[1];
                    rPtr->link[1] = stack[ht - 1];

                    if (stack[ht - 1] == root)
                    {
                        root = rPtr;
                    } else
                    {
                        stack[ht - 2]->link[dir[ht - 2]] = rPtr;
                    }
                    dir[ht] = 1;
                    stack[ht] = stack[ht - 1];
                    stack[ht - 1] = rPtr;
                    ht++;

                    rPtr = stack[ht - 1]->link[0];
                }
                if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) &&
                    (!rPtr->link[1] || rPtr->link[1]->color == BLACK))
                {
                    rPtr->color = RED;
                } else
                {
                    if (!rPtr->link[0] || rPtr->link[0]->color == BLACK)
                    {
                        qPtr = rPtr->link[1];
                        rPtr->color = RED;
                        qPtr->color = BLACK;
                        rPtr->link[1] = qPtr->link[0];
                        qPtr->link[0] = rPtr;
                        rPtr = stack[ht - 1]->link[0] = qPtr;
                    }
                    rPtr->color = stack[ht - 1]->color;
                    stack[ht - 1]->color = BLACK;
                    rPtr->link[0]->color = BLACK;
                    stack[ht - 1]->link[0] = rPtr->link[1];
                    rPtr->link[1] = stack[ht - 1];
                    if (stack[ht - 1] == root)
                    {
                        root = rPtr;
                    } else
                    {
                        stack[ht - 2]->link[dir[ht - 2]] = rPtr;
                    }
                    break;
                }
            }
            ht--;
        }
    }
}

void searchElement(User *data)
{
    struct rbNode *temp = root;
    int diff;

    while (temp != NULL)
    {
        diff = data->idNumber - temp->data->idNumber;
        if (diff > 0)
        {
            temp = temp->link[1];
        } else if (diff < 0)
        {
            temp = temp->link[0];
        } else
        {
            printf("Search Element Found!!\n");
            return;
        }
    }
    printf("Given Data Not Found in RB Tree!!\n");
    return;
}

void inorderTraversal(struct rbNode *node)
{
    if (node)
    {
        inorderTraversal(node->link[0]);
        printf("\n%d\n%s%s\n", node->data->idNumber, node->data->sign_up_date, node->data->screen_name);
        inorderTraversal(node->link[1]);
    }
    return;
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

void AddData_Head(List *list, Data data, int id)
{
    Node *addNode = (Node *) malloc(sizeof(Node));
    addNode->data = (Data)malloc(sizeof(char)*LEN);
    addNode->idNum = id;
    addNode->next = NULL;
    
    strcpy(addNode->data, data);

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

    addNode->next = NULL;
    strcpy((char *) addNode->data, data);


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
    delData = (char *) list->head->data;
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
    delData = (char *) list->head->data;

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
        delData = (char *) list->head->data;

        list->head = NULL;
        list->tail = NULL;
    }

    else if (!strcmp((char *) list->cur->data, data))
    {
        delNode = list->cur;
        delData = (char *) list->head->data;

        list->head = list->head->next;
    }

    else
    {
        while (list->cur != NULL && !strcmp((char *) list->cur->data, data))
            list->cur = list->cur->next;

        if (list->cur == NULL)
            return NULL;

        Node *before = list->head;
        while (before->next != list->cur)
            before = before->next;

        delNode = list->cur;
        delData = (char *) list->cur->data;

        if (list->cur == list->tail)
            list->tail = before;

        before->next = list->cur->next;
    }

    free(delNode);
    (list->numOfData)--;

    return delData;
}

void TweetWord_IDnum_Traverse(List *list)
{
    list->cur = list->head;

    while (list->cur != NULL)
    {
        printf("%d \n", list->cur->idNum);
        list->cur = list->cur->next;
    }

    return;
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

void GetFriendShipNum()
{
    int index = 0;
    int userIndex = 0;

    while (fgets(str, LEN, fren_File))
    {
        if (strcmp(str, "\n") == 0 || strcmp(str, "\r\n") == 0)
        {
            Total_Friendship_Records++;
            continue;
        }

        if (index == 3) { index = 0; }

        if (index == 0)
        {

            index++;
        }
        else if (index == 1)
        {

            index++;
        }

        else if (index == 2)
        {
            index++;
        }

        Total_Friendship_Records++;
    }

    Total_Friendship_Records /= 3;
}

void GetTweetsNum()
{
    int index = 0;
    int userIndex = 0;
    int i;

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
                while ((user + userIndex)->idNumber != atoi(str) && (user + userIndex) != NULL)
                    userIndex++;

                (user + userIndex)->tweetsNum++;
            }
            index++;
        }
        else if (index == 1) { index++; }

        else if (index == 2)
        {
            AddData_Head(tweet, str, (user + User_index)->idNumber);
            index++;
        }

        Total_Tweets++;
    }

    Total_Tweets /= 4;
}

int Partition(int name[], int A[], int p, int r)
{
    int x = A[r];
    int i = p - 1;
    int j, temp;

    for (j = p; j < r; j++)
    {
        if (A[j] <= x)
        {
            i++;
            temp = A[j];
            A[j] = A[i];
            A[i] = temp;

            temp = name[j];
            name[j] = name[i];
            name[i] = temp;
        }
    }

    temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;

    temp = name[i + 1];
    name[i + 1] = name[r];
    name[r] = temp;

    return i + 1;
}

void QuickSort(int name[], int A[], int p, int r)
{
    if (p < r)
    {
        int q = Partition(name, A, p, r);
        QuickSort(name, A, p, q - 1);
        QuickSort(name, A, q + 1, r);
    }
}

void Print_Top5_Most_Tweeted_User()
{
    int arr[User_index];
    int name[User_index];
    int n = User_index - 1;

    printf("%s\n\n","3. Top 5 most tweeted users");
    

    for (int i = 0; i < User_index; i++)
    {
        arr[i] = (user + i)->tweetsNum;
        name[i] = (user + i)->idNumber;
    }

    QuickSort(name, arr, 0, User_index - 1);

    printf("\t\t%s:    %s\n\n", "idNumber", "tweetsNumber");
    while (n >= User_index - 5)
    {
        printf("\t\t%8d:    %5d\n", name[n], arr[n]);
        n--;
    }

    NewLine
}

int Word_Partition(char word[Total_Tweets][LEN], int p, int r)
{
    char *x = (char*)malloc(sizeof(char)*LEN);
    char *temp;
    int i=p-1;
    int j;

    strcpy(x, word[0]);
    
    for(j=p; j<r; j++)
    {
        if(strcmp(word[j], x) >= 0)
        {
            i++;
            
            temp = word[j];
            strcpy(word[j], word[i]);
            strcpy(word[i], temp);
        }
    }
    
    temp = word[i+1];
    strcpy(word[i+1], word[r]);
    strcpy(word[r], temp);

    return i+1; 
}

void WordQuickSort(char word[Total_Tweets][LEN], int p, int r)
{
    if(p < r)
    {
        int q = Word_Partition(word, p, q);
        Word_Partition(word, p, q-1);
        Word_Partition(word, q+1, r);
    }
}

void Print_Top5_Most_Tweeted_Word()
{
    char word[Total_Tweets][LEN];
    int n = Total_Tweets;
    int i=0;
    
    tweet->cur = tweet->head;
    
    while(tweet->cur != NULL)
    {
        strcpy(word[i], tweet->cur->data);
        i++;
        tweet->cur = tweet->cur->next;
    }//strcpy(word[i++], (const char *) tweet->cur->data);

    for(i=0; i<n; i++)
        printf("%s ", word[i]);
    
    NewLine
    NewLine
    NewLine
    NewLine
    
    WordQuickSort(word, 0, n-1);
    
    for(i=0; i<n; i++)
        printf("%s ", word[i]);
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
            Print_Top5_Most_Tweeted_User();
            break;
        case 3:
            Print_Top5_Most_Tweeted_Word();
            break;
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


int main(void)
{

    GetTheUserNum();
    GetFriendShipNum();
    GetTweetsNum();


    for (int i = 0; i < User_index; i++)
        insertion((user + i));

    //inorderTraversal(root);

    
    /*for (int i = 0; i < User_index; i++)
        printf("\n%d\n%s%s", (user + i)->idNumber, (user + i)->sign_up_date, (user + i)->screen_name);*/
    
    do { Interface(); } while (Process());

    NewLine

    /*while (!IsListEmpty(tweet))
    {
        printf("  %s \n", DeleteData_Head(tweet));
    }*/


    return 0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


