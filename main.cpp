#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LEN     300
#define TRUE    1
#define FALSE   0
#define INFINITY  (int)1E10
#define NewLine     printf("\n\n");

enum graphVerx
{
    WHITE = 111,
    GRAY = 222,
    //BLACK = 333
};

enum nodeColor
{
    RED,
    BLACK
};

enum Select
{
    Top5_Most_Tweeted_User = 3,
    Find_User_Who_Tweeted_word = 4,
    Find_All_People_Who_are_Friend_of_4 = 5,
    Delete_All_Mentions_of_a_Word = 6,
    Delete_All_Users_Who_Mentioned_Word = 7
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

    List tweet_Word;
    List friendShip;

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

FILE *user_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/ETC/user.txt", "r");     //182     
FILE *fren_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/ETC/friend.txt", "r");   //1,812 
FILE *word_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/ETC/word.txt", "r");     //2,175


User *user = (User *) malloc(sizeof(User) * 200);       //allocate User
char *str = (char *) malloc(sizeof(char) * LEN);

List *tweet = (List *) malloc(sizeof(List));
List *tweetTogether_IDnum = (List *) malloc(sizeof(List));
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
                }
                else
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
                 *        YR  =>      XR   B  =>  XR   R
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
                }
                else
                {
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
        else
        {
            yPtr = stack[ht - 2]->link[0];
            if ((yPtr != NULL) && (yPtr->color == RED))
            {
                /*
                 * Red node with red child
                 *        B             R
                 *      /   \         /   \
                 *     R     R   =>  B     B
                 *            \             \
                 *             R             R
                 *
                 */
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            }
            else
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
                     *     XR  =>     YR
                     *    /            \
                     *   YR             XR
                     *   
                     * Single rotation b/w XR(node x with red color) & YR
                     */

                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[0];
                    xPtr->link[0] = yPtr->link[1];
                    yPtr->link[1] = xPtr;
                    stack[ht - 2]->link[1] = yPtr;
                }
                /*
                 *   B               YR           YB
                 *    \             /  \         /  \
                 *     YR    =>    B    XR  =>  R    XR
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
                }
                else
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
                }
                else
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
            }
            else
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

    Total_User--;
}

void AddData_Head(List *, char *, int);

User *searchElement(int main_ID)
{
    struct rbNode *temp = root;
    int diff = 0;

    while (temp != NULL)
    {
        diff = main_ID - temp->data->idNumber;

        if (diff > 0)
            temp = temp->link[1];

        else if (diff < 0)
            temp = temp->link[0];

        else
            return temp->data;
    }

    printf("%d does not exits! \n", main_ID);
    return NULL;
}

void inorderTraversal(struct rbNode *node)
{
    if (node)
    {
        inorderTraversal(node->link[0]);
        //printf("\n%d\n%s%s\n", node->data->idNumber, node->data->sign_up_date, node->data->screen_name);
        printf("%d\n", node->data->idNumber);
        inorderTraversal(node->link[1]);
    }
    return;
}


typedef struct Adj
{
    int n;
    struct Adj *next;
} Adj;

void Adj_init(Adj *self)
{
    self->n = 0;
    self->next = NULL;
}

typedef struct
{
    int color;
    int parent;
    int name;
    int n;
    Adj *first;
} Vertex;

void Vertex_init(Vertex *self)
{
    self->color = 0;
    self->parent = -1;
    self->name = 0;
    self->n = 0;
    self->first = NULL;
}

void Vertex_add(Vertex *self, Vertex *v)
{
    Adj *a = (Adj *) malloc(sizeof(Adj));
    a->n = v->n;
    a->next = self->first;
    self->first = a;
}

typedef struct
{
    Vertex super;
    int dfs_in, dfs_out;
} DFSVertex;

void DFSVertex_init(DFSVertex *self)
{
    Vertex_init(&self->super);
    self->dfs_in = 0;
    self->dfs_out = 0;
}

void print_dfsvertex(DFSVertex *vertices, int n)
{
    printf("%-8d ", vertices[n].super.name);
    printf("%-8d ", vertices[n].super.color);
    printf("%-8d ", vertices[n].super.parent);
    printf("%-8d ", vertices[n].dfs_in);
    printf("%-8d", vertices[n].dfs_out);

    printf("   \t: ");

    for (Adj *p = vertices[n].super.first; p; p = p->next)
    {
        printf("%d ", vertices[p->n].super.name);
    }

    printf("\n");
}

int dfs_time = 0;


void dfs_visit(DFSVertex *vertices, int nelem, int u)
{
    dfs_time++;
    vertices[u].dfs_in = dfs_time;
    vertices[u].super.color = GRAY;     //방문 기록 OK

    printf("%d : %d, \n", vertices[u].super.name, dfs_time);
    for (Adj *v = vertices[u].super.first; v; v = v->next)
    {
        if (vertices[v->n].super.color == WHITE)
        {
            printf("시작 %d\n", vertices[v->n].super.name);

            vertices[v->n].super.parent = u;
            dfs_visit(vertices, nelem, v->n);
        }
    }
    vertices[u].super.color = BLACK;
    dfs_time++;
    vertices[u].dfs_out = dfs_time;
    printf("%d 탈출! \n", vertices[u].super.name);
}

void dfs(DFSVertex *vertices, int nelem)
{
    for (int u = 0; u < nelem; u++)
    {
        vertices[u].super.color = WHITE;
        vertices[u].super.parent = INFINITY;
    }

    dfs_time = 0;

    for (int u = 0; u < nelem; u++)
    {
        if (vertices[u].super.n == WHITE)
        {
            dfs_visit(vertices, nelem, u);
        }
    }
}

void Tran_Vertex_add(Vertex *self, Vertex *v)
{
    Adj *a = (Adj *) malloc(sizeof(Adj));
    Adj *tmp = self->first;
    a->n = v->n;

    if (self->first == NULL)
    {
        a->next = self->first;
        self->first = a;
        return;
    }

    // Insert to tail
    while (tmp->next != NULL)
        tmp = tmp->next;

    a->next = NULL;
    tmp->next = a;
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
    addNode->data = (Data) malloc(sizeof(char) * LEN);
    addNode->idNum = id;
    addNode->next = NULL;

    if (data != NULL)
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
        delData = list->head->data;

        list->head = NULL;
        list->tail = NULL;
    }

    else if (!strcmp(list->cur->data, data))
    {
        delNode = list->cur;
        delData = list->head->data;

        list->head = list->head->next;
    }

    else
    {
        while (list->cur != NULL && !strcmp(list->cur->data, data))
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
        printf("%d -> ", list->cur->idNum);
        list->cur = list->cur->next;
    }
    printf("\n");

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
    int mainFriend = 0, subFriend = 0;
    char *str = (char *) malloc(sizeof(char) * LEN);

    /*Initiation all the user tweet list*/
    for (int i = 0; i < User_index; i++)
        InitList(&(user + i)->friendShip);

    while (fgets(str, LEN, fren_File))
    {
        if (index == 3)
        {
            index = 0;
            //continue;
        }

        if (index == 0)
        {
            /*it takes O(logN)*/
            /*because RB-Tree is a Balanced Tree*/

            if (strcmp(str, ""))
                mainFriend = atoi(str);
            index++;
        }

        else if (index == 1)
        {
            /*it takes O(logN)*/
            /*because RB-Tree is a Balanced Tree*/

            subFriend = atoi(str);

            /*temp is mainFriend structure*/
            User *temp = searchElement(mainFriend);

            if (temp)
                AddData_Head(&temp->friendShip, temp->screen_name, subFriend);
            else
                printf("%d \n", mainFriend);

            /*while ((user + i)->idNumber != mainFriend)
                i++;

            AddData_Head(&(user + i)->tweet_Word, str, subFriend);*/
            
            temp->friendsNum++;
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

        if (index == 3)
        {
            index = 0;
        }

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

            AddData_Head(tweetTogether_IDnum, str, (user + userIndex)->idNumber);
            AddData_Head(&(user + userIndex)->tweet_Word, str, (user + userIndex)->idNumber);
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

void ReadTheDataFile()
{
    NewLine
    printf("%s %d\n", "Total users: ", Total_User);
    printf("%s %d\n", "Total friendship records: ", Total_Friendship_Records);
    printf("%s %d\n", "Total tweets: ", Total_Tweets);
    NewLine
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

/*Quicsort takes O(n*logn)*/
/*change with idNum*/
void Print_Top5_Most_Tweeted_User()
{
    int arr[User_index];
    int name[User_index];
    int n = User_index - 1;

    NewLine
    printf("%s\n\n", "3. Top 5 most tweeted users");

    for (int i = 0; i < User_index; i++)
    {
        arr[i] = (user + i)->tweetsNum;
        name[i] = (user + i)->idNumber;
    }

    QuickSort(name, arr, 0, User_index - 1);

    printf("\t\t%s:    %s\n\n", "idNumber", "tweetsNumber");
    while (n >= User_index - 5)
    {
        printf("\t\t%10d:    %5d\n", name[n], arr[n]);
        n--;
    }

    NewLine
}

/*BubbleSort takes O(n^2)*/
/*change with idNumber together*/
void BubbleSort(char str[][LEN], int A[Total_Tweets], int n)
{
    int i, j;
    char *temp = (char *) malloc(sizeof(char) * 100);
    int numTemp;

    for (i = 0; i < n - 1; i++)
        for (j = 0; j < (n - 1) - i; j++)
            if (strcmp(str[j], str[j + 1]) > 0)
            {
                strcpy(temp, str[j]);
                numTemp = A[j];

                strcpy(str[j], str[j + 1]);
                strcpy(str[j + 1], temp);

                A[j] = A[j + 1];
                A[j + 1] = numTemp;
            }
    free(temp);
    return;
}

void Get_SortedData(char word[Total_Tweets][LEN], int *idNum)
{
    int i = 0;
    int n = Total_Tweets;

    tweet->cur = tweet->head;
    tweetTogether_IDnum->cur = tweetTogether_IDnum->head;

    /*list traverse  takes O(n)*/
    /*takes two array, 1) Word 2) Who tweeted that word*/

    while (tweet->cur != NULL && tweetTogether_IDnum->cur != NULL)
    {
        strcpy(word[i], tweet->cur->data);

        *(idNum + i) = tweetTogether_IDnum->cur->idNum;

        i++;

        tweet->cur = tweet->cur->next;
        tweetTogether_IDnum->cur = tweetTogether_IDnum->cur->next;
    }

    /*Sort to use counting working easily*/
    BubbleSort(word, idNum, n);

    tweet->cur = tweet->head;

}

int BinarySerach(char word[Total_Tweets][LEN], int idNum[LEN], int p, int q, char *target)
{
    int mid = (p+q)/2;
    
    if(p <= q)
    {
        if(strcmp(target, word[mid]) == 0)
            return mid;
        else if(strcmp(target, word[mid]) > 0)
            return BinarySerach(word, idNum, p, mid-1, target);
        else
            return BinarySerach(word, idNum, mid+1, q, target);
    }

    return -1;
    
}

void PrintAllFriendShip(int idNum)
{
    int i, count = 0;
    Node *cur = NULL;

    for (i = 0; i < User_index; i++)
    {
        if((user+i)->idNumber == idNum)
        {
            printf("ID NUM: %d  \n", (user + i)->idNumber);
            printf("Friends List: ");

            cur = (user + i)->friendShip.head;
            while (cur != NULL)
            {
                printf("%d -> ", cur->idNum);
                cur = cur->next;
                count++;
            }
            printf("NULL\n\n");
            break;
        }
    }
}

/*
 * select (3) == Print Top5 Most Word
 * select (4) == Print Who Tweeted Word
 * select (5) ==  Find All People Who are Friend of above user
 * select (6) ==  Delete users who mentioned a word
 * select (7) ==  Delete all users who mentioned a word
 * 
 * */

char string[LEN];

void Word_ID_RealtionShip_Func(char *str, int select)
{
    char word[Total_Tweets][LEN];
    int idNum[Total_Tweets];
    int n = Total_Tweets;
    int i = 0;

    if(!Total_Tweets)
    {
        puts("Words were all deleted\n\n");
        return;
    }

    /*idNum and word array are same as word.txt files*/
    Get_SortedData(word, idNum);

    if (select == Top5_Most_Tweeted_User)
    {
        for (i = 0; i < n; i++)
            if(idNum[i] != -1 )
                printf("%d \t->\t %s\n", idNum[i], word[i]);
    }

    else if (select == Find_User_Who_Tweeted_word)
    {
        int idx = 0, check = 0;
        char *dummy;
        getchar();
        gets(string);
        strcat(string, "\n");
        
        printf("%s", string);
        
        while(idx < Total_Tweets)
        {
            dummy = word[idx];
            
            if(strcmp(dummy, string) == 0)
            {
                if(idNum[idx] == -1)
                {
                    printf("%s is already deleted\n", string);
                    return;
                }
                
                printf("%d -> %s\n", idNum[idx], word[idx]);
                check = TRUE;
            }
            idx++;
        }
        
        if(!check)
            printf("%s does not exit in text file\n", string);
    }

    else if (select == Find_All_People_Who_are_Friend_of_4) 
    {
        int idx = 0, check = FALSE;
        char *dummy;
        
        printf("Find Word is %s\n\n", string);
        
        while(idx < Total_Tweets)
        {
            dummy = word[idx];

            if(strcmp(dummy, string) == 0)
            {
                PrintAllFriendShip(idNum[idx]);
                check = TRUE;
            }
            idx++;
        }

        if(!check)
            printf("%s does not exit in text file\n", string);
    }

    else if (select == Delete_All_Mentions_of_a_Word) 
    {
        int idx = 0;
        char *dummy;

        printf("%d\n\n", tweetTogether_IDnum->numOfData);
        
        for(int i=0; i<Total_Tweets; i++)
            memset(word[i], '\0', LEN);

        while(idx < Total_Tweets)
        {
            DeleteData_Head(tweetTogether_IDnum);
            idx++;
        }
        
        Total_Tweets = 0;
    }

    else if (select == Delete_All_Users_Who_Mentioned_Word) 
    {
        printf("Input what you wanna delete word: ");
        getchar();
        gets(string);
        strcat(string, "\n");

        int idx = 0;
        char *dummy;

        printf("Find Word is %s\n\n", string);

        while(idx < Total_Tweets)
        {
            dummy = word[idx];

            if(strcmp(dummy, string) == 0)
            {
                if(idNum[idx] == -1)
                {
                    printf("%s is already deleted\n", string);
                    return;
                }
                
                User *temp = searchElement(idNum[idx]);
                
                
                if(temp)
                {
                    printf("ID: %d is deleted \n", idNum[idx]);
                    deletion(temp);
                }
                
                Total_Tweets--;
            }
            
            idNum[idx] = -1;
            
            idx++;
        }
    }
}

void Print_Statistics()
{
    // 1. Statistics
    /*Average number of friends: xxx
    Minimum friends: xxx
    Maximum number of friends: xxx
     
    Average tweets per user: xxx
    Minium tweets per user: xxx
    Maximu tweets per user: xxx*/

    int avg_Tweet = 0;
    int min_Tweet = user->tweetsNum, max_Tweet = user->tweetsNum;
    int min_ID = 0, max_ID = 0;

    int i, key;

    int avg_Friend = 0;
    int min_Friend = user->friendShip.numOfData;
    int max_Friend = user->friendShip.numOfData;
    int min_F_ID = 0, max_F_ID = 0;

    NewLine

    for (i = 0; i < Total_User; i++)
    {
        key = (user + i)->friendShip.numOfData;

        /*The case that get the min tweet user*/
        if (min_Friend > key && key != FALSE)
        {
            min_Friend = key;
            min_F_ID = (user + i)->idNumber;
        }

        /*The case that get the max tweet user*/
        if (max_Tweet < key && key != FALSE)
        {
            max_Friend = key;
            max_F_ID = (user + i)->idNumber;
        }

        avg_Friend += key;
    }
    avg_Friend /= Total_User;

    printf("Average friend per user: %d\n", avg_Friend);
    printf("Minium friend per user: %d -> %d\n", min_F_ID, min_Friend);
    printf("Maximum friend per user: %d -> %d\n", max_F_ID, max_Friend);
    NewLine


    for (i = 0; i < Total_User; i++)
    {
        key = (user + i)->tweetsNum;

        /*The case that get the min tweet user*/
        if (min_Tweet > key && key != FALSE)
        {
            min_Tweet = key;
            min_ID = (user + i)->idNumber;
        }

        /*The case that get the max tweet user*/
        if (max_Tweet < key && key != FALSE)
        {
            max_Tweet = key;
            max_ID = (user + i)->idNumber;
        }

        avg_Tweet += key;
    }
    avg_Tweet /= Total_User;

    printf("Average tweets per user: %d\n", avg_Tweet);
    printf("Minium tweets per user: %d -> %d\n", min_ID, min_Tweet);
    printf("Maximum tweets per user: %d -> %d\n", max_ID, max_Tweet);
}

void Interface()
{
    puts("0. Read data files");
    puts("1. display statistics");
    puts("2. Top 5 most tweeted words");
    puts("3. Top 5 most tweeted users");
    puts("4. Find users who tweeted a word (e.g., ’연세대’)");
    puts("5. Find all people who are friends of the above users");
    puts("6. Delete all mentions of a word");
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
            ReadTheDataFile();
            break;
        case 1:
            Print_Statistics();
            break;
        case 2:
            Print_Top5_Most_Tweeted_User();
            break;
        case 3:
            Word_ID_RealtionShip_Func(NULL, Top5_Most_Tweeted_User);
            break;
        case 4:
            Word_ID_RealtionShip_Func(NULL, Find_User_Who_Tweeted_word);
            break;
        case 5:
            Word_ID_RealtionShip_Func(NULL, Find_All_People_Who_are_Friend_of_4);
            break;
        case 6:
            Word_ID_RealtionShip_Func(NULL, Delete_All_Mentions_of_a_Word );
            break;
        case 7:
            Word_ID_RealtionShip_Func(NULL, Delete_All_Users_Who_Mentioned_Word);
            break;
        case 8:
            /*8. Find strongly connected components
            DFS -> Denumeration -> Transpose -> Group -> Forest -> Group*/
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
    int sNum;
    
    GetTheUserNum();
    
    for (int i = 0; i < User_index; i++)
        insertion((user + i));
    
    GetFriendShipNum();
    GetTweetsNum();
    
    do
    {
        NewLine
        puts("Keep going: ");
        scanf("%d", &sNum);

        NewLine

        if (sNum)
            Interface();
        else
            break;

    } while (Process());

    NewLine

    return 0;
}