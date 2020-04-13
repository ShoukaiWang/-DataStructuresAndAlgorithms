//
//  main.c
//  DoublyCircleLinkList
//
//  Created by SK_Wang on 2020/4/13.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OK 1

#define INIT_LINKLIST_MAXSIZE 20

typedef int Status;
typedef int ElemType;

typedef struct Node {
    ElemType data;
    struct Node *prior;
    struct Node *next;
} Node;

typedef struct Node * LinkList;

Status CreateLinkList(LinkList *L) {
    *L = (LinkList)malloc(sizeof(Node));
    if (*L == NULL) return ERROR;
    (*L)->next = *L;
    (*L)->prior = *L;
    (*L)->data = -1;
    
    LinkList p = *L;
    for (int i = 10; i < 15; i++) {
        LinkList temp = (LinkList)malloc(sizeof(Node));
        if (temp == NULL) return ERROR;
        temp->data = i;
        
        p->next = temp;
        temp->prior = p;
        temp->next = (*L);
        
        p = p->next;
    }
    return OK;
}

Status LinkListInsert(LinkList *L, int place, ElemType num) {
    if (place < 1) return ERROR;
    
    LinkList p = *L;
    int i = 1;
    while (i < place && p->next != *L) {
        p = p->next;
        i++;
    }
    
    if (i > place) return ERROR;
    
    LinkList temp = (LinkList)malloc(sizeof(Node));
    if (temp == NULL) return ERROR;
    temp->data = num;
    temp->next = p->next;
    p->next = temp;
    temp->prior = p;
    if (p->next != *L) {
        temp->next->prior = temp;
    } else {
        (*L)->prior = temp;
    }
    
    return OK;
}

Status LinkListDelete(LinkList *L, int place, ElemType *e) {
    if (place < 1 || *L == NULL) return ERROR;

    LinkList p = (*L)->next;
    if (p->next == *L) {
        free(*L);
        *L = NULL;
        return OK;
    }
    
    int i = 1;
    while (i < place && p->next != *L) {
        p = p->next;
        i++;
    }
    
    if (i > place) return ERROR;
    *e = p->data;

    p->prior->next = p->next;
    p->next->prior = p->prior;

    free(p);
    return OK;
}

void TraverseLinkList(LinkList L) {
    if(L == NULL){
        printf("打印的双向链表为空!\n");
        return;
    }
    printf("双向循环链表内容:  ");
    
    LinkList temp = L->next;
    while (temp != L) {
        printf("%d_%d_%d  ", (temp->prior ? temp->prior->data : -1), temp->data, (temp->next ? temp->next->data : -1));
        temp = temp->next;
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    Status iStatus = 0;
    int temp, item, e;
    LinkList L;
    
    // create Linklist
    iStatus = CreateLinkList(&L);
    printf("双向循环链表创建成功, 打印链表:\n");
    TraverseLinkList(L);
    
//    printf("请输入插入的位置\n");
//    scanf("%d %d", &temp, &item);
//    iStatus = LinkListInsert(&L, temp, item);
//    printf("插入数据,打印链表:\n");
//    TraverseLinkList(L);
    
//    printf("请输入删除的位置\n");
//    scanf("%d",&temp);
//    iStatus = LinkListDelete(&L, temp, &e);
//    printf("删除元素: 删除位置为%d,data = %d\n", temp, e);
//    printf("删除操作之后的,双向链表:\n");
//    TraverseLinkList(L);
    
    return 0;
}
