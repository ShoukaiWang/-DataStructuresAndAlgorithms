//
//  main.c
//  HaffTreeDemo
//
//  Created by SK on 2020/4/29.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

const int MaxValue = 10000;
const int MaxBit = 4;
const int MaxN = 10;

typedef struct HaffNode {
    int weight;
    int flag;
    int parent;
    int leftChild;
    int rightChild;
} HaffNode;

typedef struct Code {
    int bit[MaxBit];
    int start;
    int weight;
} Code;

void Haffman(int weight[], int n, HaffNode *haffTree) {
    // 初始化
    for (int i = 0; i < 2 * n - 1; i++) {
        if (i < n) {
            haffTree[i].weight = weight[i];
        } else {
            haffTree[i].weight = 0;
        }
        
        haffTree[i].flag = 0;
        haffTree[i].parent = 0;
        haffTree[i].leftChild = -1;
        haffTree[i].rightChild = -1;
    }
    
    int j, m1, m2, x1, x2;
    for (int i = 0; i < n - 1; i++) {
        m2 = m1 = MaxValue;
        x2 = x1 = 0;
        for (j = 0; j < n + i; j++) {
            if (haffTree[j].weight < m1 && haffTree[j].flag == 0) {
                m2 = m1;
                m1 = haffTree[j].weight;
                x2 = x1;
                x1 = j;
            } else if (haffTree[j].weight < m2 && haffTree[j].flag == 0) {
                m2 = haffTree[j].weight;
                x2 = j;
            }
        }
        
        haffTree[x1].parent = n + i;
        haffTree[x1].flag = 1;
        
        haffTree[x2].parent = n + i;
        haffTree[x2].flag = 1;
        
        haffTree[n + i].weight = haffTree[x1].weight + haffTree[x2].weight;
        haffTree[n + i].leftChild = x1;
        haffTree[n + i].rightChild = x2;
    }
}

void HaffmanCode(HaffNode haffTree[], int n, Code haffCode[]) {
    Code *cd = (Code *)malloc(sizeof(Code));
    int child, parent;
    for (int i = 0; i < n; i++) {
        cd->start = 0;
        cd->weight = haffTree[i].weight;
        child = i;
        parent = haffTree[child].parent;
        while (parent != 0) {
            if (haffTree[parent].leftChild == child) {
                cd->bit[cd->start] = 0;
            } else {
                cd->bit[cd->start] = 1;
            }
            
            cd->start++;
            child = parent;
            parent = haffTree[child].parent;
        }
        
        int temp;
        for (int j = cd->start - 1; j >= 0; j--) {
            temp = cd->start - 1 - j;
            haffCode[i].bit[temp] = cd->bit[j];
        }
        
        haffCode[i].start = cd->start;
        haffCode[i].weight = cd->weight;
    }
    free(cd);
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    int i, j, n = 4, m = 0;
    
    //权值
    int weight[] = {2,4,5,7};
    
    //初始化哈夫曼树, 哈夫曼编码
    HaffNode *myHaffTree = malloc(sizeof(HaffNode)*2*n-1);
    Code *myHaffCode = malloc(sizeof(Code)*n);
    
    //当前n > MaxN,表示超界. 无法处理.
    if (n>MaxN)
    {
        printf("定义的n越界，修改MaxN!");
        exit(0);
    }
    
    //1. 构建哈夫曼树
    Haffman(weight, n, myHaffTree);
    //2.根据哈夫曼树得到哈夫曼编码
    HaffmanCode(myHaffTree, n, myHaffCode);
    //3.
    for (i = 0; i<n; i++)
    {
        printf("Weight = %d\n",myHaffCode[i].weight);
        for (j = 0; j<myHaffCode[i].start; j++)
            printf("%d",myHaffCode[i].bit[j]);
        m = m + myHaffCode[i].weight*myHaffCode[i].start;
         printf("\n");
    }
    printf("Huffman's WPS is:%d\n",m);
    return 0;
}
