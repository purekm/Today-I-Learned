#include <stdio.h>
#include "ArrayList.h"
#include "Point.h"

int main(void)
{
    List list; //List 생성
    int data;
    ListInit(&list); //list 초가화

    //5개의 데이터 저장
    LInsert(&list, 11);
    LInsert(&list, 11);
    LInsert(&list, 22);
    LInsert(&list, 22);
    LInsert(&list, 33);

    printf("현재 데이터의 수 %d\n",LCount(&list));

    if(LFirst(&list, &data)){
        printf("%d\n", data);
        while(LNext(&list, &data)){
             printf("%d\n", data);
        }
    }
    printf("\n\n");
    return 0;

}