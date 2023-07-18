#ifndef __DB__LINKED_LIST_H__
#define __DB__LINKED_LIST_H__

#define TRUE    1
#define FALSE 0

typedef int Data;
typedef struct _node{
    Data data;
    struct _node *next;
    struct _node *prev;
}Node;
typedef struct _CLL{
    Node *head;
    Node *cur;
    int numOfData;
}DBLinkedList;
typedef DBLinkedList List;
void ListInit(List *plist);
void LInsert(List *plist,Data data);

int LFrist(List *plist, Data *pdata);
int LNext(List *plist, Data *pdata);
int LPrevious(List *plist, Data *pdata);
int LCount(List *plist);

#endif