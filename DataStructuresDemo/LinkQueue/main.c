//
//  main.c
//  LinkQueue
//
//  Created by SK_Wang on 2020/4/13.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define QUEUE_INIT_SIZE 100

typedef int Status;
typedef int QElemType;

// 队列的链式存储
typedef struct QueueNode {
    QElemType data;
    struct QueueNode *next;
}QueueNode, *QueueNodePtr;

typedef struct {
    QueueNodePtr front;
    QueueNodePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue *Q) {
    Q->rear = Q->front = (QueueNodePtr)malloc(sizeof(QueueNode));
    if (Q->front == NULL) {
        return ERROR;
    }
    
    Q->front->next = NULL;
    Q->rear->next = NULL;
    return OK;
}

Status DestoryQueue(LinkQueue *Q) {
    while (Q->rear) {
        Q->rear = Q->front;
        Q->front = Q->front->next;
        free(Q->rear);
    }
    return OK;
}

Status ClearQueue(LinkQueue *Q) {
    QueueNodePtr p, q;
    Q->rear = Q->front;
    p = Q->front;
    Q->front = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    return OK;
}

Status QueueEmpty(LinkQueue Q) {
    return Q.front == Q.rear;
}

int QueueLength(LinkQueue Q) {
    int i = 0;
    QueueNodePtr p = Q.front;
    while (Q.rear != p) {
        i++;
        p = p->next;
    }
    return i;
}

Status EnQueue(LinkQueue *Q, QElemType e) {
    QueueNodePtr temp = (QueueNodePtr)malloc(sizeof(QueueNode));
    if (temp == NULL) {
        return ERROR;
    }
    temp->data = e;
    temp->next = NULL;
    Q->rear->next = temp;
    Q->rear = temp;
    return OK;
}

Status DeQueue(LinkQueue *Q, QElemType *e) {
    if (Q->front == Q->rear) {
        return ERROR;
    }
    
    QueueNodePtr p;
    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if (Q->rear == p) {
        Q->rear = Q->front;
    }
    
    free(p);
    return OK;
}

Status GetHead(LinkQueue Q, QElemType *e) {
    if (Q.front == Q.rear) {
        return ERROR;
    }
    
    *e = Q.front->next->data;
    return OK;
}

Status QueueTraverse(LinkQueue Q) {
    return OK;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
