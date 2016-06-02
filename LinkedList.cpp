//
// Created by 남관우 on 2016. 6. 2..
//

#include "LinkedList.h"

void InitList(List *list)
{
    list->head = NULL;
    list->cur = NULL;
    list->tail = NULL;
    
    list->numOfData = 0;
}

int AddList(List *list, LData* dataIn)
{
    Node *addNode = (Node*)malloc(sizeof(Node));
    addNode->data = (LData*)dataIn;
    addNode->next = NULL;
    
    if(!list->head)
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
    return TRUE;
}

int DeleteList(List *list)
{
    Node *delNode;
    LData *delData;
    
    list->cur = list->head;
    
    if(list->head == list->tail)
    {
        delNode = list->head;
        delData = (LData*)list->head->data;
        
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        while(list->cur->next != list->tail)
            list->cur = list->cur->next;
        
        delNode = list->tail;
        delData = (LData*)list->tail->data;
        
        list->tail = list->cur;
        list->tail->next = NULL;
    }
    
    free(delNode);
    free(delData);
    (list->numOfData)--;

    return TRUE;
}

LData* LastData(List *list)
{
    return (LData*) list->tail->data;
}

LData* FirstData(List *list)
{
    return (LData*)list->head->data;
}