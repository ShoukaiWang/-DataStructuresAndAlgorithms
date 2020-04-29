//
//  main.c
//  SqBiTree Demo
//
//  Created by SK on 2020/4/27.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */
#define MAX_TREE_SIZE 100 /* 二叉树的最大结点数 */

typedef int Status;
typedef int CElemType;
typedef CElemType SqBiTree[MAX_TREE_SIZE];
CElemType Nil = 0;

typedef struct {
    int level;
    int order;
} Position;

#pragma mrak - 二叉树的基本操作

Status InitBiTree(SqBiTree T) {
    for (int i = 0; i < MAX_TREE_SIZE; i++) {
        T[i] = Nil;
    }
    return OK;
}

Status CreateBiTree(SqBiTree T) {
    int i = 0;
    while (i < 10) {
        T[i] = i + 1;
        if (i != 0 && T[(i + 1) / 2 - 1] == Nil && T[i] != Nil) {
            return ERROR;
        }
        i++;
    }
    
    while (i < MAX_TREE_SIZE) {
        T[i++] = Nil;
    }
    
    return OK;
}

#define ClearBiTree InitBiTree

Status BiTreeEmpty(SqBiTree T) {
    return T[0] == Nil;
}

int BiTreeDepth(SqBiTree T) {
    int i;
    int j = -1;
    
    for (i = MAX_TREE_SIZE - 1; i >= 0; i--) {
        if (T[i] != Nil) {
            break;
        }
    }
    
    do {
        j++;
    } while (pow(2, j) < i);
    
    return j;
}

CElemType Value(SqBiTree T, Position e) {
    return T[(int)pow(2, e.level - 1) + e.order - 2];
}

Status Root(SqBiTree T,CElemType *e) {
    if (BiTreeEmpty(T)) {
        return ERROR;
    }
    *e = T[0];
    return OK;
}

Status Assign(SqBiTree T, Position e, CElemType value) {
    int i = (int)pow(2, e.level -1 ) + e.order - 2;
    
    //叶子结点的双亲为空
    if (value != Nil && T[(i + 1) / 2 -1] == Nil) {
        return ERROR;
    }
    
    //给双亲赋空值但是有叶子结点
    if (value == Nil && (T[i * 2 + 1] != Nil || T[i * 2 + 2] != Nil)) {
        return ERROR;
    }
    
    T[i] = value;
    return OK;
}

CElemType Parent(SqBiTree T, CElemType e) {
    if (T[0] == Nil) {
        return ERROR;
    }
    
    for (int i = 1; i < MAX_TREE_SIZE; i++) {
        if (T[i] == e) {
            return T[(i + 1) / 2 -1];
        }
    }
    
    return Nil;
}

CElemType LeftChild(SqBiTree T, CElemType e) {
    if (T[0] == Nil) {
        return ERROR;
    }
    
    for (int i = 0; i < MAX_TREE_SIZE - 1; i++) {
        if (T[i] == e) {
            return T[i * 2 + 1];
        }
    }
    
    return Nil;
}

CElemType RightChild(SqBiTree T, CElemType e) {
    if (T[0] == Nil) {
        return ERROR;
    }
    
    for (int i = 0; i < MAX_TREE_SIZE - 1; i++) {
        if (T[i] == e) {
            return T[i * 2 + 2];
        }
    }
    
    return Nil;
}

CElemType LeftSibling(SqBiTree T,CElemType e) {
    if (T[0] == Nil) {
        return ERROR;
    }
    
    for (int i = 1; i < MAX_TREE_SIZE - 1; i++) {
        if (T[i] == e && i % 2 == 0) {
            return T[i - 1];
        }
    }
    
    return Nil;
}

CElemType RightSibling(SqBiTree T,CElemType e) {
    if (T[0] == Nil) {
        return ERROR;
    }
    
    for (int i = 1; i < MAX_TREE_SIZE - 1; i++) {
        if (T[i] == e && i % 2 == 1) {
            return T[i + 1];
        }
    }
    
    return Nil;
}

Status visit(CElemType c){
    printf("%d ",c);
    return OK;
}

void LevelOrderTraverse(SqBiTree T) {
    int i = MAX_TREE_SIZE - 1;
    while (T[i] != Nil) {
        i--;
    }
    
    for (int j = 0; j <= i; j++) {
        if (T[j] != Nil) {
            visit(T[j]);
        }
    }
    printf("\n");
}

void PreTraverse(SqBiTree T, int e) {
    visit(T[e]);
    if (T[2 * e + 1] != Nil) {
        PreTraverse(T, 2 * e + 1);
    }
    
    if (T[2 * e + 2] != Nil) {
        PreTraverse(T, 2 * e + 2);
    }
}

Status PreOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T)) {
        PreTraverse(T, 0);
    }
    printf("\n");
    return OK;
}

void InTraverse(SqBiTree T, int e) {
    if (T[2 * e + 1] != Nil) {
        InTraverse(T, 2 * e + 1);
    }
    
    visit(T[e]);
    
    if (T[2 * e + 2] != Nil) {
        InTraverse(T, 2 * e + 2);
    }
}

Status InOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T)) {
        InTraverse(T, 0);
    }
    printf("\n");
    return OK;
}

void PostTraverse(SqBiTree T,int e) {
    if (T[2 * e + 1] != Nil) {
        PostTraverse(T, 2 * e + 1);
    }
    
    if (T[2 * e + 2] != Nil) {
        PostTraverse(T, 2 * e + 2);
    }
    
    visit(T[e]);
}

Status PostOrderTraverse(SqBiTree T) {
    if(!BiTreeEmpty(T)) {
        PostTraverse(T, 0);
    }
    printf("\n");
    return OK;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    Status iStatus;
    Position p;
    CElemType e;
    SqBiTree T;
    
    InitBiTree(T);
    CreateBiTree(T);
    printf("树的深度=%d\n", BiTreeDepth(T));
    
    p.level = 3;
    p.order = 2;
    e = Value(T, p);
    printf("第%d层第%d个结点的值: %d\n", p.level, p.order,e);
    
    
    iStatus = Root(T, &e);
    if (iStatus) {
        printf("二叉树的根为:%d\n", e);
    } else {
        printf("树为空,无根!\n");
    }
    
    //向树中3层第2个结点位置上结点赋值99
    e = 99;
    Assign(T, p, e);
    
    //获取树中3层第2个结点位置结点的值是多少:
    e = Value(T, p);
    printf("第%d层第%d个结点的值: %d\n", p.level, p.order, e);
    
    //找到e这个结点的双亲;
    printf("结点%d的双亲为%d_", e, Parent(T, e));
    //找到e这个结点的左右孩子;
    printf("左右孩子分别为:%d,%d\n", LeftChild(T, e), RightChild(T, e));
    //找到e这个结点的左右兄弟;
    printf("结点%d的左右兄弟:%d,%d\n", e, LeftSibling(T, e), RightSibling(T, e));
    
    Assign(T, p, 5);
    
    printf("二叉树T层序遍历:");
    LevelOrderTraverse(T);
    
    printf("二叉树T前序遍历:");
    PreOrderTraverse(T);
    
    printf("二叉树T中序遍历:");
    InOrderTraverse(T);
    
    printf("二叉树T后序遍历:");
    PostOrderTraverse(T);
    
    return 0;
}
