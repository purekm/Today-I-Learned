#include <stdio.h>
#include "ArrayList.h"
#include "Point.h"

int main(void)
{
    List list; //List ����
    int data;
    ListInit(&list); //list �ʰ�ȭ

    //5���� ������ ����
    LInsert(&list, 11);
    LInsert(&list, 11);
    LInsert(&list, 22);
    LInsert(&list, 22);
    LInsert(&list, 33);

    printf("���� �������� �� %d\n",LCount(&list));

    if(LFirst(&list, &data)){
        printf("%d\n", data);
        while(LNext(&list, &data)){
             printf("%d\n", data);
        }
    }
    printf("\n\n");
    return 0;

}