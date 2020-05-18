//
//  main.c
//  BalancedBinaryTreeDemo
//
//  Created by SK on 2020/5/18.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100

typedef int Status;

#define LH +1 // 左高
#define EH 0  // 等高
#define RH -1 // 右高

typedef struct BSTNode{
    int data;
    int bf;
    struct BSTNode *lchild,*rchild;
    
}BSTNode, *BSTree;

void R_Rotate(BSTree *p) {
    BSTree lc;
    lc = (*p)->lchild;
    (*p)->lchild = lc->rchild;
    lc->rchild = *p;
    *p = lc;
}

void L_Rotate(BSTree *p) {
    BSTree rc;
    rc = (*p)->rchild;
    (*p)->rchild = rc->lchild;
    rc->lchild = *p;
    *p = rc;
}

void LeftBalance(BSTree *T) {
    BSTree lc, rd;
    lc = (*T)->lchild;
    switch (lc->bf) {
        case LH:
            (*T)->bf = lc->bf = EH;
            R_Rotate(T);
            break;
        case RH:
            rd = lc->rchild;
            switch (rd->bf) {
                case LH:
                    (*T)->bf = RH;
                    lc->bf = EH;
                    break;
                case EH:
                    (*T)->bf = lc->bf = EH;
                    break;
                case RH:
                    (*T)->bf = EH;
                    lc->bf = LH;
                    break;
            }
            rd->bf = EH;
            L_Rotate(&(*T)->lchild);
            R_Rotate(T);
            break;;
    }
}

void RightBalance(BSTree *T) {
    BSTree rc, ld;
    rc = (*T)->rchild;
    switch (rc->bf) {
        case RH:
            (*T)->bf = rc->bf = EH;
            L_Rotate(T);
            break;
        case LH:
            ld = rc->lchild;
            switch (ld->bf) {
                case RH:
                    (*T)->bf = LH;
                    rc->bf = EH;
                    break;
                case EH:
                    (*T)->bf = rc->bf = EH;
                    break;
                case LH:
                    (*T)->bf = EH;
                    rc->bf = RH;
                    break;
            }
            ld->bf = EH;
            R_Rotate(&(*T)->rchild);
            L_Rotate(T);
            break;;
    }
}

Status InsertAVL(BSTree *T, int e, Status *taller) {
    if (!*T) {
        *T = (BSTree)malloc(sizeof(BSTNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = TRUE;
    } else {
        if (e == (*T)->data) {
            *taller = FALSE;
            return FALSE;
        }
        
        if (e < (*T)->data) {
            if (!InsertAVL(&(*T)->lchild, e, taller)) {
                return FALSE;
            } else {
                if (*taller) {
                    switch ((*T)->bf) {
                        case LH:
                            LeftBalance(T);
                            *taller = FALSE;
                            break;
                        case EH:
                            (*T)->bf = LH;
                            *taller = TRUE;
                            break;
                        case RH:
                            (*T)->bf = EH;
                            *taller = FALSE;
                            break;
                    }
                }
            }
        } else {
            if (!InsertAVL(&(*T)->rchild, e, taller)) {
                return FALSE;
            } else {
                if (*taller) {
                    switch ((*T)->bf) {
                        case RH:
                            RightBalance(T);
                            *taller = FALSE;
                            break;
                        case EH:
                            (*T)->bf = RH;
                            *taller = TRUE;
                            break;
                        case LH:
                            (*T)->bf = EH;
                            *taller = FALSE;
                            break;
                    }
                }
            }
        }
    }
    return TRUE;
}

Status SearchBST(BSTree T, int key, BSTree f, BSTree *p){
    if (!T) {
        *p = f;
        return FALSE;
    } else if (key == T->data) {
        *p = T;
        return TRUE;
    } else if (key < T->data) {
        return SearchBST(T->lchild, key, T, p);
    } else {
        return SearchBST(T->rchild, key, T, p);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("平衡二叉树 !\n");
    int a[10] = {3, 2, 1, 4, 5, 6, 7, 10, 9, 8};
    
    BSTree T = NULL;
    Status taller;
    int sum = 0;
    for(int i = 0; i < 10; i++) {
        InsertAVL(&T, a[i], &taller);
        sum += taller;
        printf("插入%d,是否增加树的高度(%d)[YES->1 / NO->0]\n", a[i], taller);
    }
    
    printf("将数组a插入到平衡二叉树后,最终形成高度为%d的平衡二叉树\n",sum);
    
    BSTree p;
    int statusValue = SearchBST(T, 10, NULL, &p);
    printf("查找%d是否成功:%d (1->YES/0->NO)\n", p->data, statusValue);
    
    return 0;
}
