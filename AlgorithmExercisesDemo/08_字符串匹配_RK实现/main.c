//
//  main.c
//  08_字符串匹配_RK实现
//
//  Created by SK_Wang on 2020/4/22.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define d 26 //d 表示进制

int isMatch(char *S, int i, char *P, int m) {
    int is, ip;
    for (is = i, ip = 0; is != m && ip != m; is++, ip++) {
        if (S[is] != P[ip]) {
            return 0;
        }
    }
    
    return 1;
}

/*
 d ^ (m - 1) 位的值
 */
int getMaxValue(int m) {
    int j = 1;
    for (int i = 0; i < m - 1; i++) {
        j = j * d;
    }
    return j;
}

int Index(char *S, char *P) {
    int n = (int)strlen(S);
    int m = (int)strlen(P);
    
    unsigned int A = 0;
    unsigned int St = 0;
    
    for (int i = 0; i != m; i++) {
        A = (d * A + (P[i] - 'a'));
        St = (d * St + (S[i] - 'a'));
    }
    
    int hValue = getMaxValue(m);
    for (int i = 0; i <= n - m; i++) {
        if (A == St && isMatch(S, i, P, m)) {
            return i + 1;
        }
        St = (St - hValue * (S[i] - 'a')) * d + (S[i + m] - 'a');
    }
    
    return -1;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    char *buf = "abcababcabx";
    char *ptrn = "abcabx";
    printf("主串为%s\n", buf);
    printf("子串为%s\n", ptrn);
    
    int index = Index(buf, ptrn);
    printf("find index : %d\n", index);
    return 0;
}
