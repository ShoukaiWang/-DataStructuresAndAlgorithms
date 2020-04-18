//
//  main.c
//  03_爬楼梯
//
//  Created by SK_Wang on 2020/4/18.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

/*
 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
 注意：给定 n 是一个正整数
 */

/*
 递归法
 f(1) = 1;
 f(2) = 2;
 f(n) = f(n - 1) + f(n - 2)
 */
int climbStairs1(int n) {
    if (n == 1) return 1;
    if (n == 2) return 2;
    return climbStairs1(n - 1) + climbStairs1(n - 2);
}

/*
 动态规划法
 */
int climbStairs2(int n) {
    if (n == 1) return 1;
    
    int *sum = (int *)malloc(sizeof(int) * n);
    sum[1] = 1;
    sum[2] = 2;
    for (int i = 3; i <= n; i++) {
        sum[i] = sum[i - 1] + sum[i - 2];
    }
    
    return sum[n];
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    printf("爬楼梯问题\n");
    int reslut = 0;
    
    reslut = climbStairs1(5);
    printf("%d\n",reslut);
    
    reslut = climbStairs2(5);
    printf("%d\n",reslut);
    return 0;
}
