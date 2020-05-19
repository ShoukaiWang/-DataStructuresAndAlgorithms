//
//  main.c
//  SortDemo
//
//  Created by SK on 2020/5/19.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 10000
#define N 9

typedef int Status;

typedef struct {
    int r[MAXSIZE + 1]; //用于存储要排序数组，r[0]用作哨兵或临时变量
    int length;
}SqList;

void swap(SqList *L, int i, int j) {
    int temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}

void print(SqList L) {
    int i;
    for(i = 1; i <= L.length; i++) {
        printf("%d,", L.r[i]);
    }
    printf("\n");
}

// 冒泡排序-对顺序表L进行交换排序
void BubbleSort0(SqList *L) {
    int i, j;
    for (i = 1; i <= L->length; i++) {
        for (j = i + 1; j <= L->length; j++) {
            if (L->r[i] > L->r[j]) {
                swap(L, i, j);
            }
        }
    }
}

// 冒泡排序-对顺序表L作冒泡排序
void BubbleSort(SqList *L) {
    int i, j;
    for (i = 1; i <= L->length; i++) {
        for (j = L->length; j > i; j--) {
            if (L->r[j - 1] > L->r[j]) {
                swap(L, j - 1, j);
            }
        }
    }
}

// 冒泡排序-对顺序表L冒泡排序进行优化
void BubbleSort2(SqList *L) {
    Status flag = TRUE;
    int i, j;
    for (i = 1; i <= L->length && flag; i++) {
        flag = FALSE;
        for (j = L->length; j > i; j--) {
            if (L->r[j - 1] > L->r[j]) {
                swap(L, j - 1, j);
                flag = TRUE;
            }
        }
    }
}

// 选择排序--对顺序表L进行简单选择排序
void SelectSort(SqList *L) {
    int i, j, min;
    for (i = 1; i <= L->length; i++) {
        min = i;
        for (j = i + 1; j <= L->length; j++) {
            if (L->r[min] > L->r[j]) {
                min = j;
            }
        }
        if (i != min) {
            swap(L, i, min);
        }
    }
}

// 直接插入排序算法--对顺序表L进行直接插入排序
void InsertSort(SqList *L) {
    int i, j;
    for (i = 2; i <= L->length; i++) {
        if (L->r[i] < L->r[i - 1]) {
            L->r[0] = L->r[i];
            for (j = i - 1; L->r[0] < L->r[j]; j--) {
                L->r[j + 1] = L->r[j];
            }
            L->r[j + 1] = L->r[0];
        }
    }
}

// 希尔排序-对顺序表L希尔排序
void ShellSort(SqList *L) {
    int i, j;
    int increment = L->length;
    do {
        increment = increment / 3 + 1;
        for (i = increment + 1; i <= L->length; i++) {
            if (L->r[i] < L->r[i - increment]) {
                L->r[0] = L->r[i];
                for (j = i - increment; j > 0 && L->r[0] < L->r[j]; j -= increment) {
                    L->r[j + increment] = L->r[j];
                }
                L->r[j + increment] = L->r[0];
            }
        }
        
    } while (increment > 1);
}

/*
 大顶堆调整函数;
 条件: 在L.r[s...m] 记录中除了下标s对应的关键字L.r[s]不符合大顶堆定义,其他均满足;
 结果: 调整L.r[s]的关键字,使得L->r[s...m]这个范围内符合大顶堆定义.
 */
void HeapAjust(SqList *L, int s, int m) {
    int j, temp;
    temp = L->r[s];
    for (j = 2 * s; j <= m; j *= 2) {
        if (j < m && L->r[j] < L->r[j + 1]) {
            j++;
        }
        if (temp >= L->r[j]) {
            break;
        }
        L->r[s] = L->r[j];
        s = j;
    }
    L->r[s] = temp;
}


void HeapSort(SqList *L) {
    int i;
    for (i = L->length / 2; i > 0; i--) {
        HeapAjust(L, i, L->length);
    }
    for (i = L->length; i > 1; i--){
        swap(L, 1, i);
        HeapAjust(L, 1, i - 1);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, 排序算法\n");
    
    int i;
//    int d[N]={9,1,5,8,3,7,4,6,2};
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20};
    SqList l0, l1, l2, l3, l4, l5, l6, l7, l8, l9, l10;
    
    for(i = 0; i < N; i++)
        l0.r[i + 1] = d[i];
    
    l0.length = N;
    l1 = l2 = l3 = l4 = l5 = l6 = l7 = l8 = l9 = l10 = l0;
    
    printf("排序前:\n");
    print(l0);
    printf("\n");
    
    //1.初级冒泡排序
    printf("初级冒泡排序:\n");
    BubbleSort0(&l0);
    print(l0);
    printf("\n");
    
    //2.冒泡排序
    printf("冒泡排序:\n");
    BubbleSort(&l1);
    print(l1);
    printf("\n");
    
    //3.冒泡排序优化
    printf("冒泡排序(优化):\n");
    BubbleSort2(&l2);
    print(l2);
    printf("\n");
    
    //4.选择排序
    printf("选择排序:\n");
    SelectSort(&l3);
    print(l3);
    printf("\n");
    
    //5.直接插入排序
    printf("直接插入排序:\n");
    InsertSort(&l4);
    print(l4);
    printf("\n");
    
    //6.希尔排序
    printf("希尔排序:\n");
    ShellSort(&l5);
    print(l5);
    printf("\n");
    
    printf("堆排序:\n");
    HeapSort(&l6);
    print(l6);
    
    printf("\n");
    return 0;
}
