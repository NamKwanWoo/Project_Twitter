//
// Created by 남관우 on 2016. 6. 2..
//

#ifndef DS_PROJECT_LINKEDLIST_H
#define DS_PROJECT_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include "User.h"

#define TRUE    1
#define FLASE   0

typedef User LData;

typedef struct _node
{
    LData* data;
    struct _node *next;
} Node;

typedef struct _list
{
    Node *head;
    Node *cur;
    Node *tail;

    int numOfData;
} List;

void InitList(List *);

int AddList(List *, LData*);

int DeleteList(List *);

LData* LastData(List *list);

LData* FirstData(List *list);

#endif //DS_PROJECT_LINKEDLIST_H
