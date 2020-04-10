//
//  main.c
//  AlgorithmExercisesDemo
//
//  Created by SK_Wang on 2020/4/9.
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

typedef int Status;
typedef int ElemType;

typedef struct Node{
    ElemType data;
    struct Node *next;
}Node;

typedef struct Node * LinkList;

Status InitList(LinkList *L){
    *L = (LinkList)malloc(sizeof(Node));
    if(*L == NULL) return ERROR;
    (*L)->next = NULL;
    return OK;
}

Status ListInsert(LinkList *L, int i, ElemType e){
    int j;
    LinkList p, s;
    p = *L;
    j = 1;
    
    while (p && j < i) {
        p = p->next;
        ++j;
    }
    
    if(!p || j > i) return ERROR;
    
    s = (LinkList)malloc(sizeof(Node));
    s->data = e;
    s->next = p->next;
    p->next = s;
    
    return OK;
}

Status ListTraverse(LinkList L) {
    LinkList p = L->next;
    while(p) {
        printf("%d  ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}


/*
 题目1:
 将2个递增的有序链表合并为一个有序链表; 要求结果链表仍然使用两个链表的存储空间,不另外占用其他的存储空间. 表中不允许有重复的数据；
 */

void mergeTwoLists(LinkList *La, LinkList *Lb, LinkList *Lc) {
    LinkList pa, pb, pc, temp;
    pa = (*La)->next;
    pb = (*Lb)->next;
    *Lc = pc = *La;
    while (pa && pb) {
        if (pa->data < pb->data) {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        } else if (pa->data > pb->data) {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        } else {
            pc->next = pa;
            pc = pa;
            pa = pa->next;

            temp = pb->next;
            free(pb);
            pb = temp;
        }
    }
    pc->next = pa == NULL ? pb : pa;
    free(*Lb);
}

/*
 题目2:
 已知两个链表A和B分别表示两个集合.其元素递增排列. 设计一个算法,用于求出A与B的交集,并存储在A链表中;
 */
void Intersection(LinkList *La, LinkList *Lb, LinkList *Lc) {
    LinkList pa, pb, pc, temp;
    pa = (*La)->next;
    pb = (*Lb)->next;
    *Lc = pc = *La;
    while (pa && pb) {
        if (pa->data < pb->data) {
            temp = pa->next;
            free(pa);
            pa = temp;
        } else if (pa->data > pb->data) {
            temp = pb->next;
            free(pb);
            pb = temp;
        } else {
            pc->next = pa;
            pc = pa;
            pa = pa->next;

            temp = pb;
            pb = pb->next;
            free(temp);
        }
    }
    
    LinkList pd = pa ? pa: pb;
    while (pd) {
        temp = pd;
        pd = pd->next;
        free(temp);
    }
    
    pc->next = NULL;
    free(*Lb);
}

/*
 题目3:
 设计一个算法,将链表中所有节点的链接方向"原地旋转",即要求仅仅利用原表的存储空间. 换句话说,要求算法空间复杂度为O(1);
 例如:L={0,2,4,6,8,10}, 逆转后: L = {10,8,6,4,2,0};
 */
void Inverse(LinkList *L) {
    LinkList p, temp;
    p = (*L)->next;
    (*L)->next = NULL;
    while (p) {
        temp = p->next;
        p->next = (*L)->next;
        (*L)->next = p;
        p = temp;
    }
}

/*
 题目4:
 设计一个算法,删除递增有序链表中值大于等于mink且小于等于maxk(mink,maxk是给定的两个参数,其值可以和表中的元素相同,也可以不同)的所有元素;
 */
void DeleteMinMax(LinkList *L, int mink, int maxk) {
    LinkList p, q, pre, temp;
    pre = *L;
    p = (*L)->next;
    while (p && p->data < mink) {
        pre = p;
        p = p->next;
    }
    
    while (p && p->data <= maxk) {
        p = p->next;
    }
    
    q = pre->next;
    pre->next = p;
    
    while (q != p) {
        temp = q->next;
        free(q);
        q = temp;
    }
}

/*
 题目5:
 设将n(n>1)个整数存放到一维数组R中, 试设计一个在时间和空间两方面都尽可能高效的算法;将R中保存的序列循环左移p个位置(0<p<n)个位置, 即将R中的数据由(x0,x1,......,xn-1)变换为(xp,xp+1,...,xn-1,x0,x1,...,xp-1).
 
 例如: pre[10] = {0,1,2,3,4,5,6,7,8,9},
      n = 10,p = 3;
      pre[10] = {3,4,5,6,7,8,9,0,1,2}
 */

void Reverse(int *pre, int left, int right) {
    int i = left;
    int j = right;
    int temp;
    while (i < j) {
        temp = pre[i];
        pre[i] = pre[j];
        pre[j] = temp;
        i++;
        j--;
    }
}

void RotateLeft(int *pre, int n, int p) {
    if (p > 0 && p < n) {
        Reverse(pre, 0, n - 1);
        Reverse(pre, 0, n -1 - p);
        Reverse(pre, n - p, n - 1);
    }
}

/*
 题目6:
  已知一个整数序列A = (a0,a1,a2,...an-1),其中(0<= ai <=n),(0<= i<=n). 若存在ap1= ap2 = ...= apm = x,且m>n/2(0<=pk<n,1<=k<=m),则称x 为 A的主元素. 例如,A = (0,5,5,3,5,7,5,5),则5是主元素; 若B = (0,5,5,3,5,1,5,7),则A 中没有主元素,假设A中的n个元素保存在一个一维数组中,请设计一个尽可能高效的算法,找出数组元素中的主元素,若存在主元素则输出该元素,否则输出-1.
 */
int MainElement(int *A, int n) {
    int x = A[0];
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (x == A[i]) {
            count++;
        } else {
            if (count > 0) {
                count--;
            } else {
                x = A[i];
                count = 1;
            }
        }
    }
    
    if (count > 0) {
        count = 1;
        for (int i = 1; i < n; i++) {
            if (A[i] == x) {
                count++;
            }
        }
    }
    
    if (count > n / 2) {
        return x;
    }
    return -1;
}

/*
 题目7:
 用单链表保存m个整数, 结点的结构为(data,link),且|data|<=n(n为正整数). 现在要去设计一个时间复杂度尽可能高效的算法. 对于链表中的data 绝对值相等的结点, 仅保留第一次出现的结点,而删除其余绝对值相等的结点.
 例如,链表A = {21,-15,15,-7,15},
 删除后的链表A={21,-15,-7};
 */
void DeleteEqualNode(LinkList *L, int n) {
    int *p = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        p[i] = 0;
    }
    LinkList q = *L;
    LinkList r = (*L)->next;
    while (r) {
        if (p[abs(r->data)] == 1) {
            q->next = r->next;
            free(r);
            r = q->next;
        } else {
            p[abs(r->data)] = 1;
            q = r;
            r = r->next;
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    Status iStatus;
    LinkList La,Lb,Lc,L;
    InitList(&La);
    InitList(&Lb);
    
    /*---------题目1--------*/
    for(int j = 10; j >= 0; j -= 2) {
        iStatus = ListInsert(&La, 1, j);
    }
    printf("La:\n");
    ListTraverse(La);

    for(int j = 11; j > 0; j -= 2) {
        iStatus = ListInsert(&Lb, 1, j);
    }
    ListInsert(&Lb, 1, 0);
    printf("Lb:\n");
    ListTraverse(Lb);

    mergeTwoLists(&La, &Lb, &Lc);
    printf("Lc:\n");
    ListTraverse(Lc);
    
    /*---------题目2--------*/
    ListInsert(&La, 1, 8);
    ListInsert(&La, 1, 6);
    ListInsert(&La, 1, 4);
    ListInsert(&La, 1, 2);
    printf("La:\n");
    ListTraverse(La);

    ListInsert(&Lb, 1, 12);
    ListInsert(&Lb, 1, 10);
    ListInsert(&Lb, 1, 8);
    ListInsert(&Lb, 1, 6);
    ListInsert(&Lb, 1, 4);
    printf("Lb:\n");
    ListTraverse(Lb);

    Intersection(&La, &Lb, &Lc);
    printf("Lc:\n");
    ListTraverse(Lc);
        
    /*---------题目3--------*/
    InitList(&L);
    for(int j = 10; j >= 0; j -= 2) {
        iStatus = ListInsert(&L, 1, j);
    }
    printf("L逆转前:\n");
    ListTraverse(L);

    Inverse(&L);
    printf("L逆转后:\n");
    ListTraverse(L);
    
     /*---------题目4--------*/
    InitList(&L);
    for(int j = 10; j >= 0; j -= 2) {
        iStatus = ListInsert(&L, 1, j);
    }
    printf("L链表:\n");
    ListTraverse(L);

    DeleteMinMax(&L, 4, 8);
    printf("删除链表mink与maxk之间结点的链表:\n");
    ListTraverse(L);
    
     /*---------题目5--------*/
    int pre[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    RotateLeft(pre, 10, 3);
    for (int i = 0; i < 10; i++) {
        printf("%d ",pre[i]);
    }
    printf("\n");

     /*---------题目6--------*/
    int A[] = {0, 5, 5, 3, 5, 7, 5, 5};

    int value = MainElement(A, 8);
    printf("数组A 主元素为: %d\n", value);

     /*---------题目7--------*/
    InitList(&L);
    ListInsert(&L, 1, 21);
    ListInsert(&L, 1, -15);
    ListInsert(&L, 1, 15);
    ListInsert(&L, 1, -7);
    ListInsert(&L, 1, 15);

    DeleteEqualNode(&L, 21);
    ListTraverse(L);
    
    return 0;
}
