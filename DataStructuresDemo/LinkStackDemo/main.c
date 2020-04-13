//
//  main.c
//  LinkStackDemo
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

// 链栈
typedef struct StackNode {
    SElemType data;
    struct StackNode *next;
}StackNode, *LinkStackPtr;

typedef struct {
    LinkStackPtr top;
    int count;
}LinkStack;

Status InitStack(LinkStack *S) {
    S->top = (LinkStackPtr)malloc(sizeof(StackNode));
    if (S->top == NULL) {
        return ERROR;
    }
    
    S->top = NULL;
    S->count = 0;
    return OK;
}

Status GetTop(LinkStack S, SElemType *e) {
    if (S.count == 0) {
        return ERROR;
    }
    
    *e = S.top->data;
    return OK;
}

Status Push(LinkStack *S, SElemType e) {
    LinkStackPtr temp = (LinkStackPtr)malloc(sizeof(StackNode));
    if (!temp) {
        return ERROR;
    }
    
    temp->data = e;
    temp->next = S->top;
    S->top = temp;
    S->count++;
    return OK;
}

Status Pop(LinkStack *S, SElemType *e) {
    if (S->count == 0) {
        return ERROR;
    }
    
    *e = S->top->data;
    LinkStackPtr p = S->top;
    S->top = S->top->next;
    free(p);
    S->count--;
    return OK;
}

Status ClearStack(LinkStack *S) {
    LinkStackPtr p, q;
    p = S->top;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    S->count = 0;
    return OK;
}

Status StackEmpty(LinkStack S) {
    return S.count == 0;
}

Status StackLength(LinkStack S) {
    return S.count;
}

Status StackTraverse(LinkStack S) {
    LinkStackPtr p = S.top;
    while (p) {
        printf("%d", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("链栈定义与实现\n");
    
    int j;
    LinkStack s;
    int e;
    if(InitStack(&s) == OK) {
        for(j = 1; j <= 10; j++) {
            Push(&s,j);
        }
    }
    printf("栈中元素依次为：");
    StackTraverse(s);
    Pop(&s, &e);
    printf("弹出的栈顶元素 e=%d\n", e);
    StackTraverse(s);
    printf("栈空否：%d(1:空 0:否)\n", StackEmpty(s));
    GetTop(s, &e);
    printf("栈顶元素 e = %d 栈的长度为%d\n", e, StackLength(s));
    ClearStack(&s);
    printf("清空栈后，栈空否：%d(1:空 0:否)\n", StackEmpty(s));
    return 0;
}
