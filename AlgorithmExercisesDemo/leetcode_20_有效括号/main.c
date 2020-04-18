//
//  main.c
//  leetcode_20_有效括号
//
//  Created by SK_Wang on 2020/4/18.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*
 给定一个只包括 `'('`，`')'`，`'{'`，`'}'`，`'['`，`']'` 的字符串，判断字符串是否有效。
 有效字符串需满足:
 1. 左括号必须用相同类型的右括号闭合。
 2. 左括号必须以正确的顺序闭合。
 注意空字符串可被认为是有效字符串。
 */
bool isValid(char * s) {
    if (*s == 0) return true;
    int len = (int)strlen(s);
    if (len & 1) return false;
    
    char stack[len];
    int top = -1;
    for (int i = 0; i < len; i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            stack[++top] = s[i];
        } else if (top == -1) {
            return false;
        } else if (s[i] == stack[top] + 1 || s[i] == stack[top] + 2) {
            top--;
        }
    }
    return top == -1;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    char * temp = "([()[]])";
    bool result = isValid(temp);
    printf("%d \n ", result);
    return 0;
}
