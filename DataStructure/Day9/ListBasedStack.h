#ifndef __LB_STACK_H__
#define __LB_STACK_H__

#define TRUE 1
#define FALSE 0

typedef int Data;
typedef struct _node{ //연결리스트 노드
    Data data;
    struct _node *next;
}Node;

typedef struct _listStack{ //연결 리스트 기반 스택
    Node *head;
}ListStack;

typedef ListStack Stack;
void StackInit(Stack *pstack); //스택 초기화
int SIsEmpty(Stack* pstack);
void SPush(Stack *pstack, Data data);
Data SPop(Stack *pstack);
Data SPeek(Stack *pstack);

#endif