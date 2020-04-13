//
//  main.c
//  StackDemo
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
#define STACK_INIT_SIZE 100

typedef int Status;
typedef int SElemType;

// 栈的顺序存储
typedef struct {
    SElemType data[STACK_INIT_SIZE];
    int top;
}SqStack;

Status InitStack(SqStack *S) {
    S->top = -1;
    return OK;
}

Status GetTop(SqStack S, SElemType *e) {
    if (S.top == -1) {
        return ERROR;
    }
    
    *e = S.data[S.top];
    return OK;
}

Status Push(SqStack *S, SElemType e) {
    if (S->top == STACK_INIT_SIZE - 1) {
        return ERROR;
    }
    
    S->top ++;
    S->data[S->top] = e;
    return OK;
}

Status Pop(SqStack *S, SElemType *e) {
    if (S->top == -1) {
        return ERROR;
    }
    
    *e = S->data[S->top];
    S->top --;
    return OK;
}

Status ClearStack(SqStack *S) {
    S->top = -1;
    return OK;
}

Status StackEmpty(SqStack S) {
    return S.top == -1;
}

Status StackLength(SqStack S) {
    return S.top + 1;
}

Status StackTraverse(SqStack S) {
    int i = 0;
    while (i <= S.top) {
        printf("%d", S.data[i++]);
    }
    printf("\n");
    return OK;
}



int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    printf("顺序栈的表示与实现!\n");
    SqStack S;
    int e;
    if (InitStack(&S) == OK) {
        for (int j = 1 ; j < 10; j++) {
            Push(&S, j);
        }
    }
    
    printf("顺序栈中元素为:\n");
    StackTraverse(S);
    
    Pop(&S, &e);
    printf("弹出栈顶元素为: %d\n", e);
    StackTraverse(S);
    printf("是否为空栈:%d\n", StackEmpty(S));
    GetTop(S, &e);
    printf("栈顶元素:%d \n栈长度:%d\n", e, StackLength(S));
    ClearStack(&S);
    printf("是否已经清空栈 %d, 栈长度为:%d\n", StackEmpty(S), StackLength(S));
    return 0;
}
