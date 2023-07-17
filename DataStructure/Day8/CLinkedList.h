#ifndef __C__LINKED_LIST_H__
#define __C__LINKED_LIST_H__

#define TRUE    1
#define FALSE 0

typedef int Data;
typedef struct _node{
    Data data;
    struct _node *next;
}Node;
typedef struct _CLL{
    Node *tail;
    Node *cur;
    Node *before;
    int numOfData;
}CList;
typedef CList List;
void ListInit(List *plist);
void LInsert(List *plist,Data data);
void LInsertFront(List *plist,Data data);

int LFrist(List *plist, Data *pdata);
int LNext(List *plist, Data *pdata);
Data LRemove(List *plist);
int LCount(List *plist);

#endif

/*원형구조로 생겨서 head을 사용하면  tail위치까지 가는데 n만큼 가야하지만
tail을 사용하면 head를 tail->next로 사용하면 되기때문에 tail만 사용함
*/