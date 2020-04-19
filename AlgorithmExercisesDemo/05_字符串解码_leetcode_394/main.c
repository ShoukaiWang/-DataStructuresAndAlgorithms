//
//  main.c
//  05_字符串解码_leetcode_394
//
//  Created by SK_Wang on 2020/4/18.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 394. 字符串解码
 链接：https://leetcode-cn.com/problems/decode-string
 给定一个经过编码的字符串，返回它解码后的字符串。
 
 编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。
 
 你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。
 
 此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。
 
 示例:
 
 s = "3[a]2[bc]", 返回 "aaabcbc".
 s = "3[a2[c]]", 返回 "accaccacc".
 s = "2[abc]3[cd]ef", 返回 "abcabccdcdcdef".
 */

/*
 思路
 1.遍历字符串 S
 2.如果当前字符不为方括号"]" 则入栈stack中;
 3.如果当前字符遇到了方括号"]" 则:
    3.1 首先找到要复制的字符,例如stack="12[a",那么我要首先获取字符a;将这个a保存在另外一个栈去tempStack;
    3.2 接下来,要找到需要备份的数量,例如stack="12[a",因为出栈过字符"a",则当前的top指向了"[",也就是等于2;
    3.3 而12对于字符串是2个字符, 我们要通过遍历找到数字12的top上限/下限的位置索引, 此时上限curTop = 2, 下限通过出栈,top = -1;
    3.4 根据范围[-1,2],读取出12保存到strOfInt 字符串中来, 并且将字符"12\0",转化成数字12;
    3.5 当前top=-1,将tempStack中的字符a,复制12份入栈到stack中来;
    3.6 为当前的stack扩容, 在stack字符的末尾添加字符结束符合'\0';
 */

char * decodeString(char * s) {
    int stackSize = 50;
    char *stack = (char *)malloc(sizeof(char) * stackSize);
    int top = -1;
    
    int length = (int)strlen(s);
    for (int i = 0; i < length; i++) {
        if (s[i] != ']') {
            if (top == stackSize - 1) {
                stack = (char *)realloc(stack, (stackSize += 50) * sizeof(char));
            }
            stack[++top] = s[i];
        } else {
            int strStackSize = 10;
            char *strStack = (char *)malloc(sizeof(char) * strStackSize);
            int strTop = -1;
            
            while (stack[top] != '[') {
                if (strTop == strStackSize - 1) {
                    strStack = (char *)realloc(strStack, sizeof(char) * (strStackSize += 10));
                }
                strStack[++strTop] = stack[top--];
            }
            
            top--; // remove '['
            
//            char kStack[11];
//            int currentTop = top;
//
//            while (top != -1 && stack[top] >= '0' && stack[top] <= '9') {
//                top--;
//            }
//
//            for (int j = top + 1; j < currentTop; j++) {
//                kStack[j - (top + 1)] = stack[j];
//            }
//
//            kStack[currentTop - (top + 1)] = '\0';
//            int curNum = atoi(kStack);
            
            int curNum = 0;
            int j = 0;
            while (top != -1 && stack[top] >= '0' && stack[top] <= '9') {
                curNum += (stack[top] - '0') * pow(10, j++);
                top--;
            }
            
            for (int k = 0; k < curNum; k++) {
                int tempTop = strTop;
                while (tempTop != -1) {
                    if (top == stackSize - 1) {
                        stack = (char *)realloc(stack, sizeof(char) * (stackSize += 50));
                    }
                    stack[++top] = strStack[tempTop--];
                }
            }
        }
    }
    char *result = (char *)realloc(stack, sizeof(char) * (top + 2));
    result[++top] = '\0';
    
    return result;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    char *s ;
    s = decodeString("12[a]");
    printf("字符编码后的结果: %s\n\n",s);
    return 0;
}

