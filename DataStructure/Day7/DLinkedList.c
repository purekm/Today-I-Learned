#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"

void ListInit(List * plist){ // ����Ʈ �ʱ�ȭ
    plist -> head = (Node*)malloc(sizeof(Node)); // ���̳�� ����
    plist -> head -> next = NULL;
    plist -> comp = NULL;
    plist -> numOfData = 0;
}

void FInsert(List *plist, LData data){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = plist->head->next; // dummy�� next �ʿ� �߰��ϴ� ��� 
    plist->head->next = newNode;
    (plist->numOfData)++;
}
void SInsert(List *plist, LData data){
    Node *newNode = (Node*)malloc(sizeof(Node));
    Node *pred = plist-> head; // ���̳�带 ����Ŵ
    newNode-> data = data;
    while(pred->next != NULL && plist->comp(data,pred-> next-> data)!=0){ 
        //����1 pred�� ����Ʈ�� ������ ����ΰ�?
        //����2 �� �����Ϳ� pred�� ���� ��忡 ����� �������� �켱���� ��
        //comp�Լ� - data�� ���� ������ �ռ��� head�� ������ 0 ��ȯ, �ƴϸ� 1 ��ȯ
        pred = pred-> next;
    }
    newNode-> next = pred->next; // newNode�� ������(next)����
    pred-> next = newNode; //newNode�� ���� ����
    (plist->numOfData)++;
}


void LInsert(List *plist,LData data){
    if(plist->comp == NULL){
        FInsert(plist,data);
    }else{
        SInsert(plist,data);
    }
}

int LFirst(List *plist, LData *pdata){ //����Ʈ ù�κ��� Ž���ϴ� ���
    if(plist->head->next == NULL){
        return FALSE;
    }
    plist-> before = plist-> head; 
    plist-> cur = plist-> head -> next;
    *pdata = plist-> cur -> data;
    return TRUE;
}

int LNext(List *plist, LData *pdata){ //����Ʈ ó�� ���ĸ� Ž���ϴ� ���
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

    plist-> before-> next = plist->cur->next; // rpos->next�� �ȵ�?
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
