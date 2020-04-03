//
//  main.c
//  CircleLinkList
//
//  Created by SK_Wang on 2020/4/3.
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
    struct Node *next;
}Node;

typedef struct Node * LinkList;


/*
 判断是否是第一次创建链表：
 YES：创建一个新结点,并使得新结点的next 指向自身；
 NO：找链表尾结点,将尾结点的next指向新结点. 新结点的next指向(*L);
 */
Status CreateLinkList(LinkList *L) {
    int item;
    LinkList temp = NULL;
    LinkList target = NULL;
    printf("Enter the value of the node and end when you enter 0\n");
    while (1) {
        scanf("%d", &item);
        if (item == 0) break;
        if (*L == NULL) {
            *L = (LinkList)malloc(sizeof(Node));
            if (!L) exit(0);
            (*L)->data = item;
            (*L)->next = *L;
            target = *L;
        } else {
            temp = (LinkList)malloc(sizeof(Node));
            if (temp == NULL) return ERROR;
            temp->data = item;
            temp->next = *L;
            target->next = temp;
            target = temp;
        }
    }
    
    return OK;
}

void TraverseLinkList(LinkList p) {
    if (p == NULL) {
        printf("打印的链表为空!\n");
        return;
    } else {
        LinkList temp;
        temp = p;
        do {
            printf("%5d", temp->data);
            temp = temp->next;
        } while (temp != p);
        printf("\n");
    }
}

Status LinkListInsert(LinkList *L, int place, int num) {
    LinkList temp = (LinkList)malloc(sizeof(Node));
    if (temp == NULL) return ERROR;
    temp->data = num;
    
    LinkList target;
    if (place == 1) {
        for (target = *L; target->next != *L; target = target->next);
        temp->next = *L;
        target->next = temp;
        *L = temp;
    } else {
        int i;
        for (target = *L, i = 1; target->next != *L && i != place - 1; target = target->next, i++);
        temp->next = target->next;
        target->next = temp;
    }
    return OK;
}

Status LinkListDelete(LinkList *L, int place) {
    if (*L == NULL) return ERROR;
    
    LinkList temp, target;
    if (place == 1) {
        if ((*L)->next == *L) {
            *L = NULL;
            return OK;
        }
        for (target = *L; target->next != *L; target = target->next);
        temp = *L;
        *L = (*L)->next;
        target->next = *L;
        free(temp);
    } else {
        int i;
        for (target = *L, i = 1; target->next != *L && i != place - 1; target = target->next, i++);
        temp = target->next;
        target->next = temp->next;
        free(temp);
    }
    
    return OK;
}

int LocateElem(LinkList L, int value) {
    int i = 1;
    LinkList p = L;
    while (p->data != value && p->next != L) {
        i++;
        p = p->next;
    }
    if (p->next == L && p->data != value) {
        return -1;
    }
    return i;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    LinkList head;
    int place, num;
    Status iStatus;
    
    iStatus = CreateLinkList(&head);
    printf("原始的链表：\n");
    TraverseLinkList(head);
    
    printf("输入要插入的位置和数据用空格隔开：");
    scanf("%d %d", &place, &num);
    iStatus = LinkListInsert(&head, place, num);
    TraverseLinkList(head);
    
    printf("输入要删除的位置：");
    scanf("%d", &place);
    LinkListDelete(&head, place);
    TraverseLinkList(head);
    
    printf("输入你想查找的值:");
    scanf("%d", &num);
    place = LocateElem(head, num);
    if (place != -1) {
        printf("找到的值的位置是place = %d\n", place);
    } else {
        printf("没找到值\n");
    }
    
    return 0;
}

