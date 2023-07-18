#include <stdio.h>
#include <stdlib.h>
#include "DBLinkedList.h"

void ListInit(List *plist){ // 리스트 초기화
    plist->head = NULL;
    plist -> numOfData = 0;
}
void LInsert(List *plist,Data data){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    newNode->next = plist->head;
    if(plist->head !=NULL){
        plist->head->prev=newNode;
    }
    newNode->prev = NULL;
    plist->head = newNode;
}

int LFirst(List *plist, Data *pdata){ //head데이터 조회
    if(plist->head == NULL){
        return FALSE;
    }
    plist->cur = plist->head;
    *pdata = plist->cur->data;
    return TRUE;
}

int LNext(List *plist, Data *pdata){ //앞으로 가면서 데이터 조회
    if(plist->cur->next == NULL){
        return FALSE;
    }
    plist->cur = plist->cur->next;
    *pdata = plist-> cur ->data;
    return TRUE;
}
int LPrevious(List* plist,Data *pdata){
    if(plist->cur->prev = NULL){
        return FALSE;
    }
    plist->cur = plist->cur->prev;
    *pdata = plist->cur->prev;
    return TRUE;
}

int LCount(List *plist){
    return plist->numOfData;
}

// 양방향인 것을 제외하고는 연결리스트와 크게 바뀌는 것 없음