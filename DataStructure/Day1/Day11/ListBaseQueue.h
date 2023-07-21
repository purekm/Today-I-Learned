#ifndef __LB_QUEUE_H__
#define __LB_QUEUE_H__

#define TRUE 1
#define FALSE 0

typedef int Data;
typedef struct _node{ //연결리스트 노드
    Data data;
    struct _node *next;
}Node;

typedef struct _lQueue{ //연결 리스트 기반 큐
    Node *front;
    Node *rear;
}LQueue;

typedef LQueue Queue;
void QueueInit(Queue *pq); //큐 초기화
int QIsEmpty(Queue *pq);
void Enqueue(Queue *pq, Data data);
Data Dequeue(Queue *pq);
Data QPeek(Queue *pq);

#endif