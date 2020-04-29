//
//  main.c
//  ThreadBiTree
//
//  Created by SK on 2020/4/29.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAX_TREE_SIZE 100 /* 二叉树的最大结点数 */

typedef int Status;
typedef char TElemType;
typedef TElemType SqBiTree[MAX_TREE_SIZE];
TElemType Nil = '#';

#pragma mark--二叉树构造

int indexs = 1;
typedef char String[24];
String str;
Status StrAssign(String T,char *chars) {
    int i;
    if(strlen(chars) > 100) {
        return ERROR;
    }
    T[0] = strlen(chars);
    for(i = 1; i <= T[0]; i++)
        T[i] =* (chars + i - 1);
    return OK;
}

#pragma mark - Thread BiTree

typedef enum {
    Link,
    Thread
} PointerTag;

typedef struct BiThrNode {
    TElemType data;
    struct BiThrNode *lchild, *rchild;
    PointerTag LTag, RTag;
} BiThrNode, *BiThrTree;

Status visit(TElemType e) {
    printf("%c ",e);
    return OK;
}

Status CreateBiThrTree(BiThrTree *T) {
    TElemType e = str[indexs++];
    if (e == Nil) {
        *T = NULL;
    } else {
        *T = (BiThrTree)malloc(sizeof(BiThrNode));
        if (T == NULL) {
            exit(OVERFLOW);
        }
        
        (*T)->data = e;
        CreateBiThrTree(&(*T)->lchild);
        if ((*T)->lchild) {
            (*T)->LTag = Link;
        }
        CreateBiThrTree(&(*T)->rchild);
        if ((*T)->rchild) {
            (*T)->RTag = Link;
        }
    }
    return OK;
}

BiThrTree pre;
void InThreading(BiThrTree p) {
    if (p) {
        InThreading(p->lchild);
        if (!p->lchild) {
            p->LTag = Thread;
            p->lchild = pre;
        } else {
            p->LTag = Link;
        }
        if (!pre->rchild) {
            pre->RTag = Thread;
            pre->rchild = p;
        } else {
            pre->RTag = Link;
        }
        
        pre = p;
        InThreading(p->rchild);
    }
}

Status InOrderThreading(BiThrTree *Thrt , BiThrTree T) {
    *Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
    if (*Thrt == NULL) {
        exit(OVERFLOW);
    }
    
    (*Thrt)->LTag = Link;
    (*Thrt)->RTag = Thread;
    (*Thrt)->rchild = (*Thrt);
    if (!T) {
        (*Thrt)->lchild = *(Thrt);
    } else {
        (*Thrt)->lchild = T;
        pre = (*Thrt);
        
        InThreading(T);
        
        pre->rchild = *Thrt;
        pre->RTag = Thread;
        
        (*Thrt)->rchild = pre;
    }
    return OK;
}

Status InOrderTraverse_Thr(BiThrTree T) {
    BiThrTree p;
    p = T->lchild;
    while (p != T) {
        while (p->LTag == Link) {
            p = p->lchild;
        }
        visit(p->data);
        
        while (p->RTag == Thread && p->rchild != T) {
            p = p->rchild;
            visit(p->data);
        }
        p = p->rchild;
    }
    
    return OK;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    BiThrTree H,T;
    
    //StrAssign(str,"ABDH#K###E##CFI###G#J##");
    StrAssign(str,"ABDH##I##EJ###CF##G##");
    
    CreateBiThrTree(&T); /* 按前序产生二叉树 */
    InOrderThreading(&H, T); /* 中序遍历,并中序线索化二叉树 */
    InOrderTraverse_Thr(H);
    printf("\n\n");
    return 0;
}
