//
//  main.c
//  09_字符串匹配_KMP算法
//
//  Created by SK_Wang on 2020/4/23.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 40
typedef int Status;
typedef int ElemType;
typedef char String[MAXSIZE]; /*  0号单元存放串的长度 */

/* 生成一个其值等于chars的串T */
Status StrAssign(String T, char * chars) {
    int i;
    if(strlen(chars) > MAXSIZE) {
        return ERROR;
    } else {
        T[0] = strlen(chars);
        for(i = 1;i <= T[0]; i++)
            T[i] = *(chars + i - 1);
        return OK;
    }
}

Status ClearString(String S) {
    S[0] = 0;
    return OK;
}

/*  输出字符串T。 */
void StrPrint(String T) {
    int i;
    for(i = 1;i <= T[0]; i++)
        printf("%c", T[i]);
    printf("\n");
}

/*  输出Next数组值。 */
void NextPrint(int next[], int length) {
    int i;
    for(i = 1; i <= length; i++)
        printf("%d", next[i]);
    printf("\n");
}

/* 返回串的元素个数 */
int StrLength(String S) {
    return S[0];
}


/*
 KMP 算法
 */

void get_next(String T, int *next) {
    int i, j;
    i = 0;
    j = 1;
    
    next[1] = 0;
    while (j < T[0]) {
        if (i == 0 || T[i] == T[j]) {
            i++;
            j++;
            next[j] = i;
        } else {
            i = next[i];
        }
    }
}

int Index_KMP(String S, String T, int pos) {
    int next[MAXSIZE];
    get_next(T, next);
    
    int i = pos;
    int j = 1;
    while (i < S[0] && j <= T[0]) {
        if (j == 0 || S[i] == T[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    
    if (j > T[0]) {
        return i - T[0];
    } else {
        return -1;
    }
}

/*
 KMP优化
 */

void get_nextVal(String T, int *next) {
    int i, j;
    i = 0;
    j = 1;
    
    next[1] = 0;
    while (j < T[0]) {
        if (i == 0 || T[i] == T[j]) {
            i++;
            j++;
            
            if (T[i] != T[j]) {
                next[j] = i;
            } else {
                next[j] = next[i];
            }
        } else {
            i = next[i];
        }
    }
}

int Index_KMP2(String S, String T, int pos) {
    int next[MAXSIZE];
    get_nextVal(T, next);
    
    int i = pos;
    int j = 1;
    while (i < S[0] && j <= T[0]) {
        if (j == 0 || S[i] == T[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    
    if (j > T[0]) {
        return i - T[0];
    } else {
        return -1;
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, KMP匹配算法实现!\n");
    int i, *p, *t;
    String s1, s2;
    int Status;
    
    /*关于next数组的求解*/
    StrAssign(s1, "aaaaax");
    printf("子串为: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int *)malloc((i + 1) * sizeof(int));
    get_next(s1, p);
    printf("Next为: ");
    NextPrint(p, StrLength(s1));
    t=(int *)malloc((i + 1) * sizeof(int));
    get_nextVal(s1, t);
    printf("NextVal为: ");
    NextPrint(t, StrLength(s1));
    printf("\n");
    
    //KMP算法调用
    StrAssign(s1, "abccabcceabc");
    printf("主串为: ");
    StrPrint(s1);
    StrAssign(s2, "abcce");
    printf("子串为: ");
    StrPrint(s2);
    Status = Index_KMP(s1, s2, 1);
    printf("主串和子串在第%d个字符处首次匹配（KMP算法）[返回位置为负数表示没有匹配] \n", Status);
    Status = Index_KMP2(s1, s2, 1);
    printf("主串和子串在第%d个字符处首次匹配（KMP_2算法）[返回位置为负数表示没有匹配] \n\n", Status);
    
    return 0;
}
