//
//  main.c
//  07_字符串匹配_BF实现
//
//  Created by SK_Wang on 2020/4/22.
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
 1. BF算法-爆发匹配算法
 思路:
 1. 分别利用计数指针i和j指示主串S和模式T中当前正待比较的字符位置,i初值为pos,j的初值为1;
 2. 如果2个串均为比较到串尾,即i和j均小于等于S和T的长度时, 则循环执行以下的操作:
 * S[i]和T[j]比较,若相等,则i 和 j分别指示串中下一个位置,继续比较后续的字符;
 * 若不相等,指针后退重新开始匹配. 从主串的下一个字符串(i = i - j + 2)起再重新和模式第一个字符(j = 1)比较;
 3. 如果j > T.length, 说明模式T中的每个字符串依次和主串S找中的一个连续字符序列相等,则匹配成功,返回和模式T中第一个字符的字符在主串S中的序号(i-T.length);否则匹配失败,返回0;
*/
int Index(String S, String T, int pos) {
    int i = pos;
    int j = 1;
    while (i <= S[0] && j <= T[0]) {
        if (S[i] == T[j]) {
            i++;
            j++;
        } else {
            i = i - j + 2;
            j = 1;
        }
    }
    
    if (j > T[0]) {
        return i - T[0];
    } else {
        return -1;
    }
    
    return 0;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    int i;
    String s1,s2;
    
    StrAssign(s1, "abcdex");
    printf("s1子串为");
    StrPrint(s1);
    
    
    StrAssign(s2, "ex");
    printf("s2子串为");
    StrPrint(s2);
    
    i = Index(s1, s2, 1);
    printf("i = %d\n",i);
    return 0;
}
