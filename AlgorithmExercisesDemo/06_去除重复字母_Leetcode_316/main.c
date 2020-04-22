//
//  main.c
//  06_去除重复字母_Leetcode_316
//
//  Created by SK_Wang on 2020/4/21.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 316. 去除重复字母（https://leetcode-cn.com/problems/remove-duplicate-letters）
 给你一个仅包含小写字母的字符串，请你去除字符串中重复的字母，使得每个字母只出现一次。需保证返回结果的字典序最小（要求不能打乱其他字符的相对位置）。
 
 示例 1:
 输入: "bcabc"
 输出: "abc"
 示例 2:
 输入: "cbacdcbc"
 输出: "acdb"
 */

/*
 思路:
 1. 判断字符串可能出现的特殊情况
 2. 用一个record数组记录字符串中字母出现的次数;
 3. 申请一个字符串栈stack用来存储去除重复字母的结果,并利用它的特性帮助我们找到正确的次序;
 4. 遍历字符串s
 5. 从0~top,遍历stack 判断当前字符s[i]是否存在于栈stack中
 如果当前字符是否存在于栈的定义一个falg 标记isExist, 0表示不存在, 1表示存在
 6.如果isExist存在,record[s[i]]位置上的出现次数减一，并继续遍历下一个字符; 表示当前的stack已经有这个字符了没有必要处理这个重复的字母;
 7.如果isExist不存在,则
 如果不存在,则需要循环一个找到一个正确的位置,然后在存储起来;
 如果不存在，跳过栈中所有比当前字符大、且后面还会出现的元素，然后将当前字符入栈
 top > -1表示栈非空
 stack[top] > s[i]表示栈顶元素比当前元素大
 record[stack[top]] > 1表示后面还会出现
 通过一个while循环找到将栈中位置错误的数据,出栈. 找当前合适的位置,则结束while循环;
 找到合理的位置后,则将当前字符s[i]入栈;
 
 8.直到遍历完所有字符后,则为字符串栈stack 添加一个结束符'\0',并返回当前字符串首地址;
 */

char * removeDuplicateLetters(char * s) {
    int len = (int)strlen(s);
    if (s == NULL && len == 0) {
        return "";
    }
    
    if (len == 1) {
        return s;
    }
    
    char record[26] = {0};
    char *stack = (char *)malloc(sizeof(char) * len << 2);
    int top = -1;
    memset(stack, 0, sizeof(char) * len << 2);
    
    for (int i = 0; i < len; i++) {
        record[s[i] - 'a']++;
    }
    
    for (int i = 0; i < len; i++) {
        int isExist = 0;
        for (int j = 0; j <= top; j++) {
            if (stack[j] == s[i]) {
                isExist = 1;
                break;
            }
        }
        
        if (isExist == 1) {
            record[s[i] - 'a']--;
        } else {
            while (top > -1 && stack[top] > s[i] && record[stack[top] - 'a'] > 1) {
                record[stack[top] - 'a']--;
                top--;
            }
            stack[++top] = s[i];
        }
    }
    
    stack[++top] = '\0';
    return stack;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    char *s ;
    s = removeDuplicateLetters("bcabc");
    printf("%s\n",s);
    
    s = removeDuplicateLetters("cbacdcbc");
    printf("%s\n",s);
    return 0;
}
