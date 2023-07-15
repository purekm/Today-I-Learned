#include <stdio.h>
#include "DLinkedList.h"

int WhoIsPrecede(int d1,int d2){ //정렬기준
    if(d1<d2) {
        return 0;
    }
    else{
        return 1;
    }
}
int main(void){
    List list;
    int data;
    ListInit(&list); // 리스트 생성 및 초기화
    
    SetSortRule(&list,WhoIsPrecede); //정렬기준 등록

    LInsert(&list,11); // 데이터 5개 저장
    LInsert(&list,11);
    LInsert(&list,22);
    LInsert(&list,22);
    LInsert(&list,33);
    
    printf("현재 데이터의 수: %d \n",LCount(&list));

    if(LFirst(&list,&data)){
        printf("%d ", data);
        while(LNext(&list,&data)){
            printf("%d ", data);
        }
    }
    printf("\n\n");

    //숫자 22검색 후 삭제
    if(LFirst(&list,&data)){
        if(data == 22){
            LRemove(&list);
        }
        while(LNext(&list,&data)){
            if(data == 22){
                LRemove(&list);
            }
        }
    }

    //삭제 후 남은 데이터 출력
    printf("현재 데이터의 수: %d \n",LCount(&list));

    if(LFirst(&list,&data)){
        printf("%d ",data);
        while(LNext(&list,&data)){
             printf("%d ",data);
        }
    }
    
    printf("\n\n");
    return 0;
}