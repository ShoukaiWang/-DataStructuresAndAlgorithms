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
    while (Q->front) {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    
    return OK;
}

Status ClearQueue(LinkQueue *Q) {
    QueueNodePtr p, q;
    Q->rear = Q->front;
    p = Q->front->next;
    Q->front->next = NULL;
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
    QueueNodePtr p;
    p = Q.front->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    Status iStatus;
    QElemType d;
    LinkQueue q;
    
    //1.初始化队列q
    iStatus = InitQueue(&q);
    
    //2. 判断是否创建成
    if (iStatus) {
        printf("成功地构造了一个空队列\n");
    }
    
    //3.判断队列是否为空
    printf("是否为空队列?%d (1:是 0:否)\n", QueueEmpty(q));
    
    //4.获取队列的长度
    printf("队列的长度为%d\n", QueueLength(q));
    
    //5.插入元素到队列中
    EnQueue(&q, -3);
    EnQueue(&q, 6);
    EnQueue(&q, 12);
    
    printf("队列的长度为%d\n", QueueLength(q));
    printf("是否为空队列?%d (1:是 0:否)\n", QueueEmpty(q));
    
    //6.遍历队列
    printf("队列中的元素如下:\n");
    QueueTraverse(q);

    //7.获取队列头元素
    iStatus = GetHead(q, &d);
    if (iStatus == OK) {
        printf("队头元素是:%d\n", d);
    }
    
    //8.删除队头元素
    iStatus =DeQueue(&q, &d);
    if (iStatus == OK) {
        printf("删除了的队头元素为:%d\n", d);
    }
    
    //9.获取队头元素
    iStatus = GetHead(q, &d);
    if (iStatus == OK) {
        printf("新的队头元素为:%d\n", d);
    }
    
    //10.清空队列
    ClearQueue(&q);
    
    //11.销毁队列
    DestoryQueue(&q);
    return 0;
}
