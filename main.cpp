#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE    1
#define FALSE   0
#define LEN     250
#define NewLine     printf("\n\n");

#define WHITE 0
#define GRAY  1

enum nodeColor
{
    RED,
    BLACK
};

struct rbNode
{
    int data, color;
    struct rbNode *link[2];
};

struct rbNode *root = NULL;

struct rbNode *createNode(int data)
{
    struct rbNode *newnode;
    newnode = (struct rbNode *) malloc(sizeof(struct rbNode));
    newnode->data = data;
    newnode->color = RED;
    newnode->link[0] = newnode->link[1] = NULL;
    return newnode;
}

void insertion(int data)
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
    /* find the place to insert the new node */
    while (ptr != NULL)
    {
        if (ptr->data == data)
        {
            printf("Duplicates Not Allowed!!\n");
            return;
        }
        index = (data - ptr->data) > 0 ? 1 : 0;
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

void deletion(int data)
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
        if ((data - ptr->data) == 0)
            break;
        diff = (data - ptr->data) > 0 ? 1 : 0;
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

void searchElement(int data)
{
    struct rbNode *temp = root;
    int diff;

    while (temp != NULL)
    {
        diff = data - temp->data;
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
        printf("%d  ", node->data);
        inorderTraversal(node->link[1]);
    }
    return;
}


// RedBlackTree
/////////////////////////////////////////////////////////////////////////////////////


typedef struct Adj
{
    int n;
    struct Adj *next;
} Adj;

typedef struct
{
    int color;
    int parent;
    char name[10];
    int n;
    Adj *first;
} Vertex;

typedef struct
{
    Vertex super;
    double d;
} BFSVertex;

typedef struct
{
    Vertex super;
    int dfs_in, dfs_out;
} DFSVertex;

typedef struct
{
    int front;
    int rear;
    int sz;
    int *buf;
} Queue;

typedef char *Data;

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

static int Total_User = 0, Total_Friendship_Records = 0, Total_Tweets = 0;
static int User_index = 0;

FILE *user_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/ETC/user.utf8", "r");     //182     
FILE *fren_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/ETC/friend.utf8", "r");   //35,453 
FILE *word_File = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/ETC/word.utf8", "r");     //1,308
User *user = (User *) malloc(sizeof(User));       //allocate User
char *str = (char *) malloc(sizeof(char) * LEN);




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Graph Part

void Adj_init(Adj *self)
{
    self->n = 0;
    self->next = NULL;
}

void Vertex_init(Vertex *self)
{
    self->color = 0;
    self->parent = -1;
    strcpy(self->name, "(none)");
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

void BFSVertex_init(BFSVertex *self)
{
    Vertex_init(&self->super);
    self->d = 1E10;
}

void DFSVertex_init(DFSVertex *self)
{
    Vertex_init(&self->super);
    self->dfs_in = 0;
    self->dfs_out = 0;
}

void Queue_init(Queue *self)
{
    self->front = 0;
    self->rear = 0;
    self->sz = 0;
    self->buf = NULL;
}

void Queue_create_queue(Queue *self, int sz)
{
    self->sz = sz;
    self->buf = (int *) malloc(sizeof(int) * sz);
}

void Queue_enqueue(Queue *self, int val)
{
    self->buf[self->rear] = val;
    self->rear = (self->rear + 1) % self->sz;
}

int Queue_dequeue(Queue *self)
{
    int res = self->buf[self->front];
    self->front = (self->front + 1) % self->sz;
    return res;
}

int Queue_is_empty(Queue *self)
{
    return self->front == self->rear;
}

void print_bfsvertex(BFSVertex *vertices, int n)
{
    printf("%-8s ", vertices[n].super.name);
    printf("%-8d ", vertices[n].super.color);
    printf("%-8d ", vertices[n].super.parent);
    printf("%-16.0f\t: ", vertices[n].d);
    for (Adj *p = vertices[n].super.first; p; p = p->next)
    {
        printf("%s ", vertices[p->n].super.name);
    }
    printf("\n");
}

void print_dfsvertex(DFSVertex *vertices, int n)
{
    printf("%-8s ", vertices[n].super.name);
    printf("%-8d ", vertices[n].super.color);
    printf("%-8d ", vertices[n].super.parent);
    printf("%-8d ", vertices[n].dfs_in);
    printf("%-8d", vertices[n].dfs_out);

    printf("   \t: ");

    for (Adj *p = vertices[n].super.first; p; p = p->next)
    {
        printf("%s ", vertices[p->n].super.name);
    }

    printf("\n");
}

void bfs(BFSVertex *vertices, int nelem, int s)
{
    Queue q;
    //Start from S
    for (int u = 0; u < nelem; u++)
    {
        if (vertices[u].super.n != s)
        {
            vertices[u].super.color = WHITE;
            vertices[u].d = 1E10;
            vertices[u].super.parent = -1;
        }
    }
    // Except for s, all init -1, White;


    vertices[s].super.color = GRAY;
    vertices[s].d = 0;
    vertices[s].super.parent = -1;

    Queue_init(&q);
    Queue_create_queue(&q, nelem);
    Queue_enqueue(&q, s);

    while (!Queue_is_empty(&q))
    {
        int u = Queue_dequeue(&q);
        for (Adj *adj_v = vertices[u].super.first; adj_v; adj_v = adj_v->next)
        {
            if (vertices[adj_v->n].super.color == WHITE)
            {
                vertices[adj_v->n].super.color = GRAY;
                vertices[adj_v->n].d = vertices[u].d + 1;
                vertices[adj_v->n].super.parent = u;
                Queue_enqueue(&q, adj_v->n);
            }
        }
        vertices[u].super.color = BLACK;
    }

    // (s), (w r), (x t v), (y u)
}

int dfs_time = 0;


void dfs_visit(DFSVertex *vertices, int nelem, int u)
{
    dfs_time++;
    vertices[u].dfs_in = dfs_time;
    vertices[u].super.color = GRAY;
    for (Adj *v = vertices[u].super.first; v; v = v->next)
    {
        if (vertices[v->n].super.color == WHITE)
        {
            vertices[v->n].super.parent = u;
            dfs_visit(vertices, nelem, v->n);
        }
    }
    vertices[u].super.color = BLACK;
    dfs_time++;
    vertices[u].dfs_out = dfs_time;
}

void dfs(DFSVertex *vertices, int nelem)
{
    for (int u = 0; u < nelem; u++)
    {
        vertices[u].super.color = WHITE;
        vertices[u].super.parent = -1;
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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// User Part

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// List Part

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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Get each part

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
                while ((user + userIndex)->idNumber != atoi(str) && (user + userIndex) != NULL)
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





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






////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main Part

int main(void)
{
    /*InitUser(user);

    GetTheUserNum(user, user_File, str);
    GetFriendShipNum(user, fren_File, str);
    GetTweetsNum(user, word_File, str);

    do { Interface(); } while (Process());

    printf("%d\n\n", user->tweetsNum);
*/

    int ch, data;
    while (1) {
        printf("1. Insertion\t2. Deletion\n");
        printf("3. Searching\t4. Traverse\n");
        printf("5. Exit\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter the data to insert:");
                scanf("%d", &data);
                insertion(data);
                break;
            case 2:
                printf("Enter the data to delete:");
                scanf("%d", &data);
                deletion(data);
                break;
            case 3:
                printf("Enter the search element:");
                scanf("%d", &data);
                searchElement(data);
                break;
            case 4:
                inorderTraversal(root);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("You have entered wrong option!!\n");
                break;
        }
        printf("\n");
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////