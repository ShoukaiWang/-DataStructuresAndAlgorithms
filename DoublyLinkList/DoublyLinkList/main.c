//
//  main.c
//  DoublyLinkList
//
//  Created by SK_Wang on 2020/4/6.
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
    (*L)->prior = NULL;
    (*L)->next = NULL;
    (*L)->data = -1;
    
    LinkList p = *L;
    for (int i = 10; i <= 20; i++) {
        LinkList temp = (LinkList)malloc(sizeof(Node));
        if (temp == NULL) return ERROR;
        temp->data = i;
        temp->prior = NULL;
        temp->next = NULL;
        
        p->next = temp;
        temp->prior = p;
        p = p->next;
    }
    return OK;
}

Status LinkListInsert(LinkList *L, int place, ElemType num) {
    if (place < 1) return ERROR;
    LinkList temp = (LinkList)malloc(sizeof(Node));
    temp->prior = NULL;
    temp->next = NULL;
    temp->data = num;
    
    LinkList p = *L;
    for (int i = 1; i < place && p != NULL; i++) {
        p = p->next;
    }
    
    if (p == NULL) return ERROR;
    
    if (p->next == NULL) {
        p->next = temp;
        temp->prior = p;
    } else {
        temp->next = p->next;
        p->next->prior = temp;
        p->next = temp;
        temp->prior = p;
    }
    
    return OK;
}

Status LinkListDelete(LinkList *L, int place, ElemType *e) {
    if (place < 1 || *L == NULL) return ERROR;

    LinkList p = *L;
    for (int i = 1; i < place && p != NULL; i++) {
        p = p->next;
    }
    if (p == NULL) return ERROR;
    
    LinkList deleteItem = p->next;
    *e = deleteItem->data;

    p->next = deleteItem->next;
    if (deleteItem->next != NULL) {
        deleteItem->next->prior = p;
    }
    free(deleteItem);
    
    return OK;
}

Status LinkListDeleteValue(LinkList *L, ElemType value) {
    LinkList p = *L;
    while (p) {
        if (p->data == value) {
            p->prior->next = p->next;
            if (p->next != NULL) {
                p->next->prior = p->prior;
            }
            free(p);
            break;
        }
        p = p->next;
    }
    return OK;
}

int LocateElem(LinkList L, ElemType value) {
    LinkList p = L->next;
    int i = 1;
    while (p) {
        if (p->data == value) {
            return i;
        }
        i++;
        p = p->next;
    }
    return ERROR;
}

void TraverseLinkList(LinkList L) {
    LinkList temp = L->next;
    if(temp == NULL){
        printf("打印的双向链表为空!\n");
        return;
    }
    
    while (temp) {
        printf("%d_%d_%d  ", temp->prior ? temp->prior->data : -1, temp->data, temp->next ? temp->next->data : -1);
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
    printf("iStatus = %d\n",iStatus);
    printf("链表创建成功, 打印链表:\n");
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
    
//    printf("请输入你要删除的内容\n");
//    scanf("%d", &temp);
//    iStatus = LinkListDeleteValue(&L, temp);
//    printf("删除指定data域等于%d的结点,双向链表:\n",temp);
//    TraverseLinkList(L);
    
//    printf("请输入你要查找的内容\n");
//    scanf("%d", &temp);
//    ElemType index = LocateElem(L, temp);
//    printf("在双向链表中查找到数据域为%d的结点,位置是:%d\n", temp, index);
    
    return 0;
}
