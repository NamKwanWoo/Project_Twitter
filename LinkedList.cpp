//
// Created by 남관우 on 2016. 6. 4..
//

#include "LinkedList.h"

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
    if (list->head == NULL)
        return TRUE;
    else
        return FALSE;
}

void AddData_Head(List *list, Data data)
{
    Node *addNode = (Node *) malloc(sizeof(Node));
    addNode->data = (char *)malloc(sizeof(char)*LEN);
    
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
    addNode->data = (char *)malloc(sizeof(char)*LEN);

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
    free(delData);
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