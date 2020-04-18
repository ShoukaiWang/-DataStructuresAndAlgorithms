//
//  main.c
//  00_数制转换
//
//  Created by SK_Wang on 2020/4/18.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>

/*
 给定一个整数，将其转化为八进制，并以字符串形式输出。
 */

void conversion(int N) {
    int stack[N];
    int top = -1;
    while (N) {
        stack[++top] = N % 8;
        N = N / 8;
    }
    while (top != -1) {
        printf("%d", stack[top--]);
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    conversion(12345);
    return 0;
}
