## 函数指针

```cpp
int max(int a, int b) return (a >= b)? a : b;
int (*p) (int, int); // 去掉*p的括号的话，就变成了返回值类型为指针的函数声明语句
p = max; // 函数入口地址
int m = p (5, 3);
```


# 递归

```cpp
int fibs(n){
    if (n <= 1) return n;
    return fibs[n - 1] + fibs[n - 2];
}
```

调用次数：
$$
\begin{split}
fibs(0) = 1 \\
fibs(1) = 1 \\
fibs(2) = 1 \\
fibs(3) = 2 \\
... \\
fibs(n) = 1 + fibs(n - 1) + fibs(n - 2) \\

X0 = 2 = 2 * fibs(1) \\
X1 = 2 = 2 * fibs(2) \\
X2 = 4 = 2 * fibs(3) \\
... \\
Xn = Xn-1 + Xn-2 = 2 * fibs(n + 1) \\
=> NumCall(n) = 2 * fibs(n + 1) - 1 \\
\end{split}
$$
