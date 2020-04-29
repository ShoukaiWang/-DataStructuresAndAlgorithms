//
//  main.c
//  LinkBiTreeDemo
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
typedef char CElemType;
typedef CElemType SqBiTree[MAX_TREE_SIZE];
CElemType Nil = ' ';

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

#pragma mark - BiTree

typedef struct BiTNode {
    CElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

Status visit(CElemType e) {
    printf("%c ", e);
    return OK;
}

Status InitBiTree(BiTree *T) {
    *T = NULL;
    return OK;
}

void DestroyBiTree(BiTree *T) {
    if (*T) {
        if ((*T)->lchild) {
            DestroyBiTree(&(*T)->lchild);
        }
        if ((*T)->rchild) {
            DestroyBiTree(&(*T)->rchild);
        }
        free(T);
        *T = NULL;
    }
}

#define ClearBiTree DestroyBiTree

void CreateBiTree(BiTree *T) {
    CElemType e = str[indexs++];
    if (e == '#') {
        *T = NULL;
    } else {
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (T == NULL) {
            return;
        }
        
        (*T)->data = e;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}

Status BiTreeEmpty(BiTree T) {
    return T == NULL;
}

int BiTreeDepth(BiTree T) {
    if (T == NULL) {
        return 0;
    }
    
    int i, j;
    if (T->lchild) {
        i = BiTreeDepth(T->lchild);
    } else {
        i = 0;
    }
    
    if (T->rchild) {
        j = BiTreeDepth(T->rchild);
    } else {
        j = 0;
    }
    
    return i > j ? i + 1 : j + 1;
}

CElemType Root(BiTree T) {
    if (BiTreeEmpty(T)) {
        return Nil;
    }
    return T->data;
}

CElemType Value(BiTree p) {
    return p->data;
}

void Assign(BiTree p, CElemType value) {
    p->data=value;
}

void PreOrderTraverse(BiTree T) {
    if (T == NULL) {
        return;
    }
    printf("%c", T->data);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

void InOrderTraverse(BiTree T) {
    if (T == NULL) {
        return;
    }
    InOrderTraverse(T->lchild);
    printf("%c", T->data);
    InOrderTraverse(T->rchild);
}

void PostOrderTraverse(BiTree T) {
    if (T == NULL) {
        return;
    }
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    printf("%c", T->data);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    int i;
    BiTree T;
    CElemType e1;
    
    InitBiTree(&T);
    StrAssign(str, "ABDH#K###E##CFI###G#J##");
    
    CreateBiTree(&T);
    printf("二叉树是否为空%d(1:是 0:否),树的深度=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
    
    e1 = Root(T);
    printf("二叉树的根为: %c\n",e1);
    
    printf("\n前序遍历二叉树:");
    PreOrderTraverse(T);
    
    printf("\n中序遍历二叉树:");
    InOrderTraverse(T);
    
    printf("\n后序遍历二叉树:");
    PostOrderTraverse(T);
    
    return 0;
}
