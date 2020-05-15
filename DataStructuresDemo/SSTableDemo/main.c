//
//  main.c
//  SSTableDemo
//
//  Created by SK on 2020/5/15.
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

// 顺序查找
int Sequential_Search(int *a, int n, int key) {
    for (int i = 1; i <= n; i++) {
        if (a[i] == key) {
            return i;
        }
    }
    return 0;
}

int Sequential_Search_Guard(int *a, int n, int key) {
    a[0] = key;
    int i = n;
    while (a[i] != key) {
        i--;
    }
    return i;
}

// 折半查找算法
int Binary_Search(int *a, int n, int key) {
    int mid;
    int low = 1;
    int high = n;
    while (low <= high) {
        mid = (high + low) >> 1;
        if (key < a[mid]) {
            high = mid - 1;
        } else if (key > a[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return 0;
}

// 插值查找
int Interpolation_Search(int *a, int n, int key) {
    int mid;
    int low = 1;
    int high = n;
    while (low <= high) {
        mid = low + (high - low) * (key - a[low]) / (a[high] - a[low]);
        if (key < a[mid]) {
            high = mid - 1;
        } else if (key > a[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return 0;
}

//5.斐波拉契查找
int F[100]; /* 斐波那契数列 */
int Fibonacci_Search(int *a, int n, int key) {
    int low, high, mid, i, k;
    low = 1;
    high = n;
    k = 0;
    while (n > F[k] - 1) {
        k++;
    }
    for(i = n; i < F[k] - 1; i++)
        a[i] = a[n];
    
    while (low <= high) {
        mid = low + F[k-1] - 1;
        if (key < a[mid]) {
            high = mid - 1;
            k = k - 1;
        } else if(key > a[mid]){
            low = mid + 1;
            k = k - 2;
        } else {
            if (mid <= n) {
                return mid;
            } else {
                return n;
            }
        }
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, 静态查找!\n\n");
    int a[MAXSIZE + 1], i, result;
    int arr[MAXSIZE] = {0,1,16,24,35,47,59,62,73,88,99};
    for (i = 0; i <= MAXSIZE; i++) {
        a[i] = i;
    }
    
    //1,顺序查找
    result = Sequential_Search(a, MAXSIZE, MAXSIZE);
    printf("顺序查找:%d\n",result);
    
    //2,顺序查找_哨兵
    result = Sequential_Search_Guard(a, MAXSIZE, 1);
    printf("顺序查找_哨兵:%d \n", result);
    
    //3.折半查找
    result = Binary_Search(arr, 10, 62);
    printf("折半查找:%d \n",result);
    
    //4.插值查找
    result = Interpolation_Search(arr, 10, 62);
    printf("插值查找:%d \n",result);
    
    //5.斐波拉契查找
    //斐波拉契数列计算;
    F[0] = 0;
    F[1] = 1;
    for(i = 2; i < 100; i++) {
        F[i] = F[i-1] + F[i-2];
    }
    result = Fibonacci_Search(arr, 10, 99);
    printf("斐波拉契查找:%d \n",result);
    
    result = Fibonacci_Search(arr, 10, 59);
    printf("斐波拉契查找:%d \n",result);
    
    printf("\n");
    return 0;
}
