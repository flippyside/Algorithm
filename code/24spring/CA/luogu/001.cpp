#include<iostream>
#include<vector>
#include<algorithm>
#include<stdio.h>
using namespace std;

/*
高精度加法
*/
const int MAX = 1e5;

int main() {
    char s1[MAX] = {};
    char s2[MAX] = {};
    int a[MAX] = {}; // 加数A
    int b[MAX] = {}; // 加数B
    int c[MAX] = {}; // 和

    cin >> s1 >> s2;
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    for (int i = 0; i < l1; i++) {
        a[i] = s1[l1 - 1 - i] - '0';
    }
    for (int i = 0; i < l2; i++) {
        b[i] = s2[l2 - 1 - i] - '0';
    }

    int add = 0; // 进位
    int len = max(l1, l2); // 不需要再加1，因为进位的可能性
    for (int i = 0; i < len; i++) {
        c[i] = a[i] + b[i] + add; // 加上进位
        add = c[i] / 10; // 计算进位
        c[i] %= 10; // 更新当前位的值
    }
    if (add > 0) { // 如果最高位还有进位
        c[len] = add; // 加上最后的进位
        len++; // 结果长度加1
    }
    for (int i = len - 1; i >= 0; i--) {
        cout << c[i];
    }
}
