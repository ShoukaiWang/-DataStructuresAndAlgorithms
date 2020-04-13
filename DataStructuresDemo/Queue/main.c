//
//  main.c
//  Queue
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

// 队列的顺序存储
typedef struct {
    QElemType data[QUEUE_INIT_SIZE];
    int front;
    int rear;
}SqQueue;

Status InitQueue(SqQueue *Q) {
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

Status ClearQueue(SqQueue *Q) {
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

Status QueueEmpty(SqQueue Q) {
    return Q.front == Q.rear;
}

Status GetHead(SqQueue Q, QElemType *e) {
    if (Q.front == Q.rear) {
        return ERROR;
    }
    *e = Q.data[Q.front];
    return OK;
}

Status EnQueue(SqQueue *Q, QElemType e) {
    if ((Q->rear + 1) % QUEUE_INIT_SIZE == Q->front) {
        return ERROR;
    }
    
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % QUEUE_INIT_SIZE;
    return OK;
}

Status DeQueue(SqQueue *Q, QElemType *e) {
    if (Q->front == Q->rear) {
        return ERROR;
    }
    
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % QUEUE_INIT_SIZE;
    return OK;
}

Status QueueTraverse(SqQueue Q) {
    int i;
    i = Q.front;
    while ((i + Q.front) != Q.rear) {
        printf("%d", Q.data[i]);
        i = (i + 1) % QUEUE_INIT_SIZE;
    }
    return OK;
}

int QueueLength(SqQueue Q) {
    return (Q.rear - Q.front + QUEUE_INIT_SIZE) % QUEUE_INIT_SIZE;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    Status j;
    int i = 0;
    QElemType d;
    SqQueue Q;
    InitQueue(&Q);
    printf("初始化队列后，队列空否？%u(1:空 0:否)\n", QueueEmpty(Q));
    
    printf("入队:\n");
    while (i < 10) {
        EnQueue(&Q, i);
        i++;
    }
    QueueTraverse(Q);
    printf("队列长度为: %d\n", QueueLength(Q));
    printf("现在队列空否？%u(1:空 0:否)\n", QueueEmpty(Q));
    printf("出队:\n");
    
    //出队
    DeQueue(&Q, &d);
    printf("出队的元素:%d\n", d);
    QueueTraverse(Q);
    
    //获取队头
    j = GetHead(Q, &d);
    if(j)
        printf("现在队头元素为: %d\n", d);
    
    ClearQueue(&Q);
    printf("清空队列后, 队列空否？%u(1:空 0:否)\n", QueueEmpty(Q));
    
    return 0;
}
