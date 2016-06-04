//
// Created by 남관우 on 2016. 6. 2..
//

#ifndef DS_PROJECT_LINKEDLIST_H
#define DS_PROJECT_LINKEDLIST_H


#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE    0

#define LEN     250

typedef char* Data;

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




#endif //DS_PROJECT_LINKEDLIST_H



