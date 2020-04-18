//
//  main.c
//  04_每日温度
//
//  Created by SK_Wang on 2020/4/18.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

/*
 根据每日 气温 列表，请重新生成一个列表，对应位置的输出是需要再等待多久温度才会升高超过该日的天数。如果之后都不会升高，请在该位置用 0 来代替。
 提示：气温 列表长度的范围是 [1, 30000]。每个气温的值的均为华氏度，都是在 [30, 100] 范围内的整数。
 */

/*
 思路:
 1.创建一个result 结果数组.
 2.默认reslut[TSize-1] = 0;
 3.从TSize-2个元素遍历到第一个元素[TSize-2,0];
 4.从[i+1,TSize]遍历,j+=result[j];
    -若T[i]<T[j],那么Result = j - i;
    -若reuslt[j] == 0,则表示后面不会有更大的值,那么当前值就应该也是0;
 */

int * dailyTemperatures(int * T, int TSize, int * returnSize) {
    *returnSize = TSize;
    int *result = (int *)malloc(sizeof(int) * TSize);
    result[TSize - 1] = 0;
    
    for (int i = TSize - 2; i >= 0; i--) {
        for (int j = i + 1; j < TSize; j += result[j]) {
            if (T[i] < T[j]) {
                result[i] = j - i;
                break;
            } else if (result[j] == 0) {
                result[i] = 0;
                break;
            }
        }
    }
    return result;
}

/*
思路:
1. 初始化一个栈(用来存储索引),value数组
2. 栈中存储的是元素的索引值index;
3. 遍历整个温度数组从[0,TSize];
   (1).如果栈顶元素<当前元素,则将当前元素索引index-栈顶元素index,计算完毕则将当前栈顶元素移除,将当前元素索引index 存储到栈中; 出栈后,只要栈不为空.继续比较,直到栈顶元素不能满足T[i] > T[stack_index[top-1]]
(2).如果当前的栈为空,则直接入栈;
(3).如果当前的元素小于栈顶元素,则入栈
(4).while循环结束后,当前元素也需要入栈;
*/
int * dailyTemperatures2(int * T, int TSize, int * returnSize) {
    *returnSize = TSize;
    int *result = (int *)malloc(sizeof(int) * TSize);
    int *stack_index = (int *)malloc(sizeof(int) * TSize);
    int top = 0;
    int tIndex;
    
    for (int i = 0; i < TSize; i++) {
        result[i] = 0;
    }
    
    for (int i = 0; i < TSize; i++) {
        while (top > 0 && T[i] > T[stack_index[top - 1]]) {
            tIndex = stack_index[top - 1];
            result[tIndex] = i - tIndex;
            top--;
        }
        
        stack_index[top] = i;
        top++;
    }
    
    return result;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int test[10]= {73, 74, 75, 71, 69, 72, 76, 73};
    int  *result;
    int  returnSize;
    
    result = dailyTemperatures2(test, 8, &returnSize);
    
    printf("\n");
    for (int i = 0; i < returnSize;i++ ) {
        printf("%d ",test[i]);
    }
    printf("\n");
    
    for (int i = 0; i < returnSize;i++ ) {
        printf("%d ",result[i]);
    }
    printf("\n");
    return 0;
}
