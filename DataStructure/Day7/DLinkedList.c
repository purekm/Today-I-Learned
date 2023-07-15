#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"

void ListInit(List * plist){ // 리스트 초기화
    plist -> head = (Node*)malloc(sizeof(Node)); // 더미노드 생성
    plist -> head -> next = NULL;
    plist -> comp = NULL;
    plist -> numOfData = 0;
}

void FInsert(List *plist, LData data){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = plist->head->next; // dummy의 next 쪽에 추가하는 방식 
    plist->head->next = newNode;
    (plist->numOfData)++;
}
void SInsert(List *plist, LData data){
    Node *newNode = (Node*)malloc(sizeof(Node));
    Node *pred = plist-> head; // 더미노드를 가리킴
    newNode-> data = data;
    while(pred->next != NULL && plist->comp(data,pred-> next-> data)!=0){ 
        //조건1 pred가 리스트의 마지막 노드인가?
        //조건2 새 데이터와 pred의 다음 노드에 저장된 데이터의 우선순위 비교
        //comp함수 - data가 정렬 순서상 앞서서 head에 가까우면 0 반환, 아니면 1 반환
        pred = pred-> next;
    }
    newNode-> next = pred->next; // newNode의 오른쪽(next)연결
    pred-> next = newNode; //newNode의 왼쪽 연결
    (plist->numOfData)++;
}


void LInsert(List *plist,LData data){
    if(plist->comp == NULL){
        FInsert(plist,data);
    }else{
        SInsert(plist,data);
    }
}

int LFirst(List *plist, LData *pdata){ //리스트 첫부분을 탐색하는 방식
    if(plist->head->next == NULL){
        return FALSE;
    }
    plist-> before = plist-> head; 
    plist-> cur = plist-> head -> next;
    *pdata = plist-> cur -> data;
    return TRUE;
}

int LNext(List *plist, LData *pdata){ //리스트 처음 이후를 탐색하는 방식
    if(plist->cur->next == NULL){
        return FALSE;
    }
    plist-> before = plist-> cur; 
    plist-> cur = plist-> cur -> next;
    *pdata = plist-> cur -> data;
    return TRUE;
}

LData LRemove(List *plist){
    Node *rpos = plist-> cur;
    LData rdata = rpos -> data;

    plist-> before-> next = plist->cur->next; // rpos->next는 안돼?
    plist->cur = plist->before;
    free(rpos);
    (plist->numOfData)--;
    return rdata;
}

int LCount(List *plist){
    return plist->numOfData;
}

void SetSortRule(List *plist,int(*comp)(LData d1,LData d2)){
    plist->comp = comp;
}
