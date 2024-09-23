index

- 正余弦函数

# 正余弦函数

泰勒级数：

$$
\sum_{n=0}^{\inf}\frac{f^{(n)}(a)}{n!}(x-a)^n
$$

a = 0时，称作麦克劳林级数

$$
\sin x = \sum_{n=0}^{\inf}\frac{(-1)^n}{(2n+1)!}x^{2n+1}=x-\frac{x^3}{3!}+\frac{x^5}{5!}-...
$$

$$
\cos x = \sum_{n=0}^{\inf}\frac{(-1)^n}{(2n)!}x^{2n}=1-\frac{x^2}{2!}+\frac{x^4}{4!}-...
$$


```cpp

long double sin_(long double x){ // sin1 = 0.841471
// sin2 = 0.90929742682
    long double res = 0, ele = 1, xx = x, sign = 1;
    for(int i = 0; i < TIME; i++){
        if(i != 0) ele *= (2 * i) * (2 * i + 1); // (2n+1)!
        res += sign * (xx / ele);
        sign *= -1; // (-1)^n
        xx *= x * x; // x^(2n+1)
    }
    return res;
}

long double cos_(long double x){ // cos1 = 0.540302
    long double res = 0, ele = 1, xx = 1, sign = 1;
    for(int i = 0; i < TIME; i++){
        if(i != 0) ele *= (2 * i) * (2 * i - 1); // (2n)!
        res += sign * (xx / ele);
        sign *= -1; // (-1)^n
        xx *= x * x; // x^(2n)
    }
    return res;
}

```

如何加速？
