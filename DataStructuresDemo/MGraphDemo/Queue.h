//
//  Queue.h
//  MGraphDemo
//
//  Created by SK on 2020/5/2.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define QUEUE_INIT_SIZE 100

typedef int Status;
typedef int QElemType;

typedef struct {
    QElemType data[QUEUE_INIT_SIZE];
    int front;
    int rear;
} SqQueue;

#include <stdio.h>

Status InitQueue(SqQueue *Q);
Status QueueEmpty(SqQueue Q);
Status EnQueue(SqQueue *Q, QElemType e);
Status DeQueue(SqQueue *Q, QElemType *e);


#endif /* Queue_h */
