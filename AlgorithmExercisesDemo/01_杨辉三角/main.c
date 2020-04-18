//
//  main.c
//  01_杨辉三角
//
//  Created by SK_Wang on 2020/4/18.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

/*
 给定一个非负整数 num，生成杨辉三角的前 num 行。
 在杨辉三角中，每个数是它左上方和右上方的数的和。
 1. 第一层循环行数i: 默认[i][0] = 1,[i][i] = 1
 2. 第二层循环控制列数j : triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j]
 */

int** generate(int numRows, int * returnSize) {
    *returnSize = numRows;
    int ** res = (int **)malloc(sizeof(int *) * numRows);
    for (int i = 0; i < numRows; i++) {
        res[i] = (int *)malloc(sizeof(int) * i);
        res[i][0] = 1;
        res[i][i] = 1;
        
        for (int j = 1; j < i; j++) {
            res[i][j] = res[i - 1][j - 1] + res[i - 1][j];
        }
    }
    return res;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    printf("杨辉三角问题\n");
    int numRows = 5;
    int returnSize;
    int **returnResult;
    
    returnResult =  generate(numRows, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0;  j<=i; j++) {
            printf(" %d ",returnResult[i][j]);
        }
        printf("]\n");
    }
    return 0;
}
