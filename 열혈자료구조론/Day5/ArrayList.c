#include <stdio.h>
#include "ArrayList.h"

void Listinit(List *plist){ //초기화
    (plist -> numOfData) = 0;
    (plist -> curPosition) = -1; //아무 대상도 가리키지 않음
}

void LInsert(List *plist, LData data){ // 데이터 저장
    if((plist -> numOfData) >= LIST_LEN){
        printf("저장이 불가능 합니다\n");
        return;
    }
    plist-> arr[plist->numOfData] = data;
    (plist-> numOfData)++;
}

void LFirst(List *plist, LData *pdata){ //첫 데이터 참조
    if (plist -> numOfData == 0){
        return FALSE;
    }
    (plist -> curPosition) = 0;
    *pdata = plist -> arr[0]; //pdata가 가리키는 공간에 데이터 저장
    return TRUE;
}

void LNext(List *plist, LData *pdata){ // 두 번째 이후 데이터 참조
    if(plist->curPosition >= (plist-> numOfData)-1){ //더 이상 참조할 데이터가 없다면
        return FALSE;
    }
    (plist->curPosition)++;
    *pdata = plist->arr[plist->curPosition];
    return TRUE;
} 

