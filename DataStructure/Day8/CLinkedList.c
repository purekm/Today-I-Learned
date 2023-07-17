#include <stdio.h>
#include <stdlib.h>
#include "CLinkedList.h"

void ListInit(List *plist){ // 리스트 초기화
    plist->tail = NULL;
    plist ->cur = NULL;
    plist ->before = NULL;
    plist -> numOfData = 0;
}

void LInsertFront(List *plist,Data data){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    if(plist-> tail == NULL){ //Node가 없을때
        plist ->tail = newNode;
        newNode-> next = newNode;
    }else{
        newNode -> next = plist->tail-> next; // Node의 앞뒤를 연결해주고 tail 이동
        plist-> tail-> next = newNode;
        plist-> tail = newNode;
    }
    (plist->numOfData)++; 
}

int LFirst(List *plist, Data *pdata){ //head데이터 조회
    if(plist->tail == NULL){
        return FALSE;
    }
    plist->before = plist->tail;
    plist-> cur = plist->tail->next; //tail->next는 head를 가리킴
    *pdata = plist->cur->data;
    return TRUE;
}

int LNext(List *plist, Data *pdata){ //앞으로 가면서 데이터 조회
    if(plist->tail == NULL){
        return FALSE;
    }
    plist->before = plist->cur;
    plist->cur = plist->cur->next;
    *pdata = plist-> cur ->data;
    return TRUE;
}
Data LRemove(List *plist){
    Node *rpos = plist->cur;
    Data rdata= rpos->data;

    if(rpos == plist->tail){
        if(plist-> tail == plist->tail->next) //노드가 한개 이하
            plist->tail = NULL;
        else
            plist->tail = plist->before;
    }
    plist->before->next = plist->cur->next; // 삭제되는 rpos노드와의 연결 삭제
    plist->cur = plist->before;

    free(rpos);
    (plist->numOfData)--;
    return rdata;
}

int LCount(List *plist){
    return plist->numOfData;
}